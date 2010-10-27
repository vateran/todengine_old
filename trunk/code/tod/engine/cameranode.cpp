#include "tod/engine/cameranode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"
#include "tod/engine/shader.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(CameraNode, AbstractCameraNode);

//-----------------------------------------------------------------------------
CameraNode::CameraNode():
fov_(3.14f/4.0f), aspectRatio_(1.3333f), near_(0.1f), far_(1000.0f)
{
    // empty

    ori_.identity();
}


//-----------------------------------------------------------------------------
CameraNode::~CameraNode()
{   
    // empty
}


//-----------------------------------------------------------------------------
void CameraNode::renderCamera(SceneServer* scene_server)
{
    Matrix44 trans;
    trans.setTranslation(-pos_.x_, -pos_.y_, -pos_.z_);

    Matrix44 rot;
    rot.setRotateQuaternion(Quaternion(-ori_.x_, -ori_.y_, -ori_.z_, ori_.w_));

    view_ = trans * rot;


    projection_.perspectiveFovLH(fov_, aspectRatio_, near_, far_);
    //view_ = camera_.getMatrix();
    
    Renderer::instance()->setTransform(TRANSFORM_VIEW, view_);
    Renderer::instance()->setTransform(TRANSFORM_PROJECTION, projection_);
}


//-----------------------------------------------------------------------------
void CameraNode::moveForward(float dist)
{
    Vector3 look;
    look.x_ = view_.m13_;
    look.y_ = view_.m23_;
    look.z_ = view_.m33_;
    look.normalize();
    look *= dist;

    pos_ += look;


    /*Vector3 move(camera_.at_);
    move.normalize();
    move *= dist;
    camera_.eye_ += move;

    camera_.viewMatrix_.lookAtLH(camera_.eye_, camera_.at_, camera_.up_);    */

    /*camera_.translateZ(dist);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());*/
}


//-----------------------------------------------------------------------------
void CameraNode::moveSideward(float dist)
{
    /*camera_.translateX(dist);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());*/
}


Vector3 TransformAxis(const Quaternion& orientation, const Vector3& axis)
{
	// 인자로 주어진 현재의 카메라 방향인 orientation 사원수로 부터 회전축을 먼저 구한다.
	// orientation으로부터 right, up, look 방향벡터를 구할 수 있다.
	// 인자 axis를 (1,0,0)으로 하면 right, (0,1,0)이면 up, (0,0,1)이면 look으로 변환한다.

	// 카메라 회전을 나타내는 orientation으로부터 회전축을 먼저 구한다.
	Matrix44 rot;
    rot.setRotateQuaternion(orientation);

	// 인자로 받은 축 벡터를 회전시켜 새로운 축을 만든다.
    Vector3 new_axis(axis);
    new_axis.transformCoord(rot);

/*    new_axis.x_ = axis.x_ * rot.m11_ + axis.y_ * rot.m21_ + axis.z_ * rot.m31_ + rot.m41_; 
	new_axis.y_ = axis.x_ * rot.m12_ + axis.y_ * rot.m22_ + axis.z_ * rot.m32_ + rot.m42_;
	new_axis.z_ = axis.x_ * rot.m13_ + axis.y_ * rot.m23_ + axis.z_ * rot.m33_ + rot.m43_;*/

	return new_axis;
}


//-----------------------------------------------------------------------------
#include <d3dx9.h>
void CameraNode::rotate(float yaw, float pitch, float roll)
{
	// right 방향으로 회전
	Quaternion q;
    q.identity();

	// 사원수로 right 벡터를 구해서 주어진 각도만큼 right 벡터방향으로 회전하는 사원수 rot를 구한다.
    q.rotationAxis(TransformAxis(ori_, Vector3(1.0f, 0.0f, 0.0f)), pitch);

	ori_ *= q;	// 카메라 방향인 orientation 사원수에 rot 사원수를 곱하여 회전효과를 만든다.

    ori_.normalize();


    /*static float yaw_ = 0, pitch_ = 0, roll_ = 0;

    yaw_ += yaw;
    pitch_ += pitch;
    roll_ += roll;

    Quaternion q;
    q.identity();
    q.rotationYawPitchRoll(yaw_, pitch_, roll_);

    Matrix44 m;
    m.identity();
    m.setRotateQuaternion(q);    

    Vector3 at(0, 0, 1), cross(1, 0, 0), up(0, 1, 0);

    at.transformCoord(m);
    cross.transformCoord(m);
    up.transformCoord(m);

    camera_.cross_ = cross;
    camera_.at_ = at;
    camera_.up_ = up;

    camera_.viewMatrix_.lookAtLH(camera_.cross_, camera_.at_, camera_.up_);    */

return;

    /*Quaternion a;
    a.identity();

    D3DXQuaternionMultiply((D3DXQUATERNION*)&a, (D3DXQUATERNION*)&x);
    D3DXQuaternionMultiply((D3DXQUATERNION*)&a, (D3DXQUATERNION*)&y);
    D3DXQuaternionMultiply((D3DXQUATERNION*)&a, (D3DXQUATERNION*)&z);

    Matrix44 m;
    m.identity();
    m.m11_ = cross.x_;  m.m12_ = cross.y_;  m.m13_ = cross.z_; 
    m.m11_ = up.x_;     m.m12_ = up.y_;     m.m13_ = up.z_; 
    m.m11_ = at.x_;     m.m12_ = at.y_;     m.m13_ = at.z_; 

    camera_.at_.transformCoord(m);
    //camera_.at_.transformCoord(this->getTransform());

    camera_.cross_.transformCoord(m);
    //camera_.cross_.transformCoord(this->getTransform());

    camera_.up_.transformCoord(m);
    //camera_.up_.normalize();

    camera_.viewMatrix_.lookAtLH(camera_.cross_, camera_.at_, camera_.up_);

/*
    D3DXQUATERNION q;
    D3DXQuaternionRotationAxis(&q, (D3DXVECTOR3*)&camera_.cross_, xx);

    D3DXMatrixRotationQuaternion((D3DXMATRIX*)(&camera_.viewMatrix_), &q);
*/

    /*Vector3 eye = camera_.getEye();
    Vector3 at = camera_.getAt();
    Vector3 up = camera_.getUp();

    // target
    Quaternion t_view(roll), t_cross(pitch), t_up(yaw);

    // camera
    Quaternion c_view(camera_.getView());
    Quaternion c_cross(camera_.getCross());
    Quaternion c_up(camera_.getUp());   

    //interpolation
    c_view.slerp(t_view, 0.95f);
    c_cross.slerp(t_cross, 0.95f);
    c_up.slerp(t_up, 0.95f);

    camera_.view_ = c_view.getVector3();
    camera_.cross_ = c_cross.getVector3();
    camera_.up_ = c_up.getVector3();

    Matrix44 m;
    m.identity();
    m.m11_ = camera_.cross_.x_; m.m12_ = camera_.cross_.y_; m.m13_ = camera_.cross_.z_; 
    m.m11_ = camera_.up_.x_;    m.m12_ = camera_.up_.y_;    m.m13_ = camera_.up_.z_; 
    m.m11_ = camera_.view_.x_;  m.m12_ = camera_.view_.y_;  m.m13_ = camera_.view_.z_; 

    eye.transformCoord(m);
    at.transformCoord(m);
    up.transformCoord(m);
    up.normalize();

    camera_.viewMatrix_.lookAtLH(eye, at, up);*/
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateX(float angle)
{
    camera_.rotateX(angle);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateY(float angle)
{
    camera_.rotateY(angle);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateZ(float angle)
{
    camera_.rotateZ(angle);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::onChangedWindowSize(int width, int height)
{
    aspectRatio_ =
        static_cast<float>(width) / 
        static_cast<float>(height);
}


//-----------------------------------------------------------------------------
bool CameraNode::hasCamera() const
{
    return true;
}


//-----------------------------------------------------------------------------
void CameraNode::bindProperty()
{
    BIND_PROPERTY(float, fov, &setFOV, &getFOV);
    BIND_PROPERTY(float, aspect_ratio, &setAspectRatio, &getAspectRatio);
    BIND_PROPERTY(float, near, &setNear, &getNear);
    BIND_PROPERTY(float, far, &setFar, &getFar);
}
