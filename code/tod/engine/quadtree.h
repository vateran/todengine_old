#ifndef TOD_ENGINE_NODE_QUADTREE_H
#define TOD_ENGINE_NODE_QUADTREE_H
/**
    @ingroup TodEngine
    @class tod::engine::QuadTree
    @brief 
*/

#include <list>
#include "tod/core/uri.h"
#include "tod/core/bbox.h"
#include "tod/core/node.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class QuadTree
    {
    public:
        class Node;
        class Element;

    public:
        QuadTree();
        virtual~QuadTree();

        void initialize(int depth, const core::BBox& box);
        void render(const core::Matrix44& view_proj);

        void insert(Element* elm, const core::BBox& box);
        void update(Element* elm, const core::BBox& box);
        void remove(Element* elm);

        int getNumNodes(int level);
        int getNodeIndex(int level, int col, int row);

    public:
        /// node in quad tree
        class Node
        {
        public:
            typedef std::list<Element*> Elements;

        public:
            Node();
            virtual~Node();

            /// recursively initialize the node
            void initialize(QuadTree* qtree, int level, int col, int row);
            /// get the node's level
            int level() const;
            /// get the node's column
            int column() const;
            /// get the node's row
            int row() const;
            /// access to elements list
            Elements& elements();
            /// compute the node's bounding box
            const core::BBox& getBoundingBox() const;
            /**
                recursively find the smallest child node which
                contains the bounding box
            */
            Node* findContainmentNode(const core::BBox& box);
            /// add element to node
            void addElement(Element* elm);
            /// remove element from node
            void removeElement(Element* elm);
            /// recursively render visible elements
            void render(
                const core::Matrix44& view_proj,
                core::BBox::ClipStatus clip_status);

        private:
            int level_;
            int column_;
            int row_;

            Elements elements_;
            QuadTree::Node* children_[4];
            core::BBox bbox_;

        };

        /// an element in the tree, derive subclass customized render() method
        class Element : public core::Node
        {
        public:
            Element();
            virtual~Element();
            DECLARE_CLASS(Element, core::Node);

            /// render the element (override in subclass)
            virtual void render(
                const core::Matrix44& view_proj,
                core::BBox::ClipStatus clip_status);

        private:
            friend class QuadTree;
            friend class QuadTree::Node;

            QuadTree::Node* node_;
        };

    private:
        /// quad tree depth
        int treeDepth_;
        /// global bounding box
        core::BBox bbox_;
        /// base chunk bounding box
        core::Vector3 baseNodeSize_;
        std::vector<Node> nodes_;

    private:
        friend class Node;

    };
}
}
}

#endif // TOD_ENGINE_NODE_TERRAINNODE_H
