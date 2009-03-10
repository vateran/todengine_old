#include "tod/engine/abstractcameranode.h"

#include "tod/core/simplepropertybinder.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(AbstractCameraNode, ShaderNode);

//-----------------------------------------------------------------------------
AbstractCameraNode::AbstractCameraNode()
{
    // empty
}


//-----------------------------------------------------------------------------
AbstractCameraNode::~AbstractCameraNode()
{
    // empty
}


//-----------------------------------------------------------------------------
void AbstractCameraNode::setRenderPathSection(const String& name)
{
    renderPathSection_ = name;
}


//-----------------------------------------------------------------------------
const String& AbstractCameraNode::getRenderPathSection() const
{
    return renderPathSection_;
}


//-----------------------------------------------------------------------------
void AbstractCameraNode::setViewMatrix(const Matrix44& m)
{
    view_ = m;
}


//-----------------------------------------------------------------------------
void AbstractCameraNode::setProjectionMatrix(const Matrix44& m)
{
    projection_ = m;
}


//-----------------------------------------------------------------------------
const Matrix44& AbstractCameraNode::getViewMatrix() const
{
    return view_;
}


//-----------------------------------------------------------------------------
const Matrix44& AbstractCameraNode::getProjectionMatrix() const
{
    return projection_;
}


//-----------------------------------------------------------------------------
void AbstractCameraNode::bindProperty()
{
    BIND_PROPERTY(const String&, renderpath_section,
        &setRenderPathSection, &getRenderPathSection);
    BIND_PROPERTY(const Matrix44&, view_matrix,
        &setViewMatrix, &getViewMatrix);
    BIND_PROPERTY(const Matrix44&, projection_matrix,
        &setProjectionMatrix, &getProjectionMatrix);
}
