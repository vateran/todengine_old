#include "tod/engine/quadtree.h"

#include "tod/core/assert.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
QuadTree::QuadTree():
treeDepth_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
QuadTree::~QuadTree()
{

}


//-----------------------------------------------------------------------------
void QuadTree::initialize(int depth, const BBox& box)
{
    tod_assert(depth > 0);
    treeDepth_ = depth;
    bbox_ = box;

    int base_demension = 1 << (depth - 1);
    baseNodeSize_.x_ = bbox_.size().x_ / base_demension;
    baseNodeSize_.y_ = bbox_.size().y_;
    baseNodeSize_.z_ = bbox_.size().z_ / base_demension;

    int num_nodes = getNumNodes(depth);
    nodes_.resize(num_nodes);
    nodes_[0].initialize(this, 0, 0, 0);
    
    // make sure all nodes have been initialized
    for (int i = 0; i < num_nodes; ++i)
    {
        tod_assert(nodes_[i].level() >= 0);
    }
}


//-----------------------------------------------------------------------------
/**
    Call render on all visible elements.
*/
void QuadTree::render(const Matrix44& view_proj)
{
    nodes_[0].render(view_proj, BBox::CLIPSTATUS_CLIPPED);
}


//-----------------------------------------------------------------------------
/**
    This inserts an elements into the quad tree.
*/
void QuadTree::insert(Element* elm, const BBox& box)
{
    tod_assert(elm);

    // find the smallest node which completely encloses the element's bbox
    Node* node = nodes_[0].findContainmentNode(box);
    if (node)
    {
        node->addElement(elm);
    }
    else
    {
        // NOTE: technically, the node is outside of the world,
        // just attach it to the toplevel node
        nodes_[0].addElement(elm);
    }
}


//-----------------------------------------------------------------------------
/**
    This updates an element in the quad tree. Call this method if the
    bounding box of the element changes.
*/
void QuadTree::update(Element* elm, const BBox& box)
{
    tod_assert(elm);

    // NOTE: this could be made more efficient by walking from the current
    // element's node upward to the first containing parent node, then
    // downward to the smallest containing child cell...
    // instead we just start at the root
    remove(elm);
    insert(elm, box);
}


//-----------------------------------------------------------------------------
/**
    Removes an element from the quad tree
*/
void QuadTree::remove(Element* elm)
{
    tod_assert(elm);
    tod_assert(0 != elm->node_);
    elm->node_->removeElement(elm);
}


//-----------------------------------------------------------------------------
/**
    Computes number of nodes in a level, including its child nodes.
*/
int QuadTree::getNumNodes(int level)
{
    return 0x55555555 & ((1 << level * 2) - 1);
}


//-----------------------------------------------------------------------------
/**
    Computes a linear chunk index for a chunk address consisting of level,
    col and row.
*/
int QuadTree::getNodeIndex(int level, int col, int row)
{
    tod_assert((col >= 0) && (col < (1 << level)));
    tod_assert((row >= 0) && (row < (1 << level)));
    return getNumNodes(level) + (row << level) + col;
}


//-----------------------------------------------------------------------------
IMPLEMENT_CLASS(QuadTree::Element, Node);


//-----------------------------------------------------------------------------
QuadTree::Element::Element()
{
    // empty
}


//-----------------------------------------------------------------------------
QuadTree::Element::~Element()
{
    // empty
}


//-----------------------------------------------------------------------------
/**
    Render a quad tree element. This virtual method should be overwritten
    in a subclass.

    The method is called with the current view_proj matrix and a clip
    status as arguments. The clip status is either CLIPSTATUS_INSIDE or
    CLIPSTATUS_CLIPPED. If the clip_status is CLIPSTATUS_INSIDE, the element
    is guaranteed to be visible and can be rendered immediately.
    When clip_status is SLIPSTATUS_CLIPPED check using the view_proj matrix
    and the element's bounding box should be performed.
*/
void QuadTree::Element::render
(const Matrix44& /*view_proj*/, BBox::ClipStatus /*clip_status*/)
{
    // empty
}


//-----------------------------------------------------------------------------
QuadTree::Node::Node():
level_(-1), column_(0), row_(0)
{
    for (int i = 0; i < 4; ++i)
        children_[i] = 0;
}


//-----------------------------------------------------------------------------
QuadTree::Node::~Node()
{
    // empty
}


//-----------------------------------------------------------------------------
void QuadTree::Node::initialize(QuadTree* qtree, int level, int col, int row)
{
    tod_assert(qtree);
    tod_assert(level_ == -1);
    tod_assert(level >= 0);
    tod_assert(col >=0 && col < (1 << level));
    tod_assert(row >=0 && row < (1 << level));

    // store address
    level_ = level;
    column_ = col;
    row_ = row;

    // update my bounding box
    float level_factor = float(1 << (qtree->treeDepth_ - 1 - level_));
    static Vector3 center;
    static Vector3 extend;
    const Vector3& base_size = qtree->baseNodeSize_;
    const BBox& tree_bbox = qtree->bbox_;
    Vector3 tree_size = tree_bbox.size();

    center.x_ = ((column_ + 0.5f) * level_factor * base_size.x_) - (tree_size.x_ * 0.5f);
    center.y_ = tree_bbox.center().y_;
    center.z_ = ((row_ + 0.5f) * level_factor * base_size.z_) - (tree_size.z_ * 0.5f);
    
    extend.x_ = level_factor * base_size.x_ * 0.5f;
    extend.y_ = tree_bbox.extends().y_;
    extend.z_ = level_factor * base_size.z_ * 0.5f;

    bbox_.set(center, extend);

    // recurse into children
    int child_level = level_ + 1;
    if (child_level < qtree->treeDepth_)
    {
        for (int i = 0; i < 4; ++i)
        {
            int child_col = 2 * column_ + (i & 1);
            int child_row = 2 * row_ + ((i & 2) >> 1);
            int child_index = qtree->
                getNodeIndex(child_level, child_col, child_row);
            children_[i] = &(qtree->nodes_[child_index]);
            children_[i]->initialize(qtree, child_level, child_col, child_row);
        }
    }
}


//-----------------------------------------------------------------------------
int QuadTree::Node::level() const
{
    return level_;
}


//-----------------------------------------------------------------------------
int QuadTree::Node::column() const
{
    return column_;
}


//-----------------------------------------------------------------------------
int QuadTree::Node::row() const
{
    return row_;
}


//-----------------------------------------------------------------------------
QuadTree::Node::Elements& QuadTree::Node::elements()
{
    return elements_;
}


//-----------------------------------------------------------------------------
const BBox& QuadTree::Node::getBoundingBox() const
{
    return bbox_;
}


//-----------------------------------------------------------------------------
/**
    This finds the smallest child node which completely contains the
    given bounding box. Calls itself recursively.
*/
QuadTree::Node* QuadTree::Node::findContainmentNode(const BBox& box)
{
    if (bbox_.contains(box))
    {
        // recurse into children
        if (children_[0] != 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                Node* contain_node = children_[i]->findContainmentNode(box);
                if (contain_node)
                    return contain_node;
            }
        }

        // not contained in children, but still contained in this
        return this;
    }
    else
    {
        return 0;
    }
}


//-----------------------------------------------------------------------------
void QuadTree::Node::addElement(Element* elm)
{
    tod_assert(elm);
    elm->node_ = this;
    elements_.push_back(elm);
}


//-----------------------------------------------------------------------------
void QuadTree::Node::removeElement(Element* elm)
{
    tod_assert(elm && elm->node_ == this);
    elm->node_ = 0;
    elm->detach();
}



//-----------------------------------------------------------------------------
/**
    Recursively renders visible node elements by invoking the Element::render()
    method on visible elements.
*/
void QuadTree::Node::render
(const Matrix44& view_proj, BBox::ClipStatus clip_status)
{
    tod_assert(clip_status != BBox::CLIPSTATUS_OUTSIDE);

    // view frustum culling (we don't need to check for culling if one
    // of our parent was already fully inside)
    if (BBox::CLIPSTATUS_CLIPPED == clip_status)
    {
        clip_status = bbox_.clipStatus(view_proj);
        if (BBox::CLIPSTATUS_OUTSIDE == clip_status)
        {
            // fully outside, return and break recursion.
            return;
        }
    }

    // render own elements...
    for (Elements::iterator i = elements_.begin();
         i != elements_.end(); ++i)
         (*i)->render(view_proj, clip_status);

    // ...and recurse into children
    if (0 != children_[0])
    {
        for (int i = 0; i < 4; ++i)
        {
            children_[i]->render(view_proj, clip_status);
        }
    }
}
