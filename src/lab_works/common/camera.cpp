#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace M3D_ISICG
{
	void Camera::setScreenSize( const int p_width, const int p_height )
	{
		_screenWidth  = p_width;
		_screenHeight = p_height;
		_aspectRatio  = float( _screenWidth ) / _screenHeight;
		_updateVectors();
		_computeViewMatrix();
		_computeProjectionMatrix();
	}

	void Camera::moveFront( const float p_delta )
	{
		_position -= _invDirection * p_delta;
		_computeViewMatrix();
	}

	void Camera::moveRight( const float p_delta )
	{
		_position += _right * p_delta;
		_computeViewMatrix();
	}

	void Camera::moveUp( const float p_delta )
	{
		_position += _up * p_delta;
		_computeViewMatrix();
	}

	void Camera::rotate( const float p_yaw, const float p_pitch )
	{
		_yaw   = glm::mod( _yaw + p_yaw, 360.f );
		_pitch = glm::clamp( _pitch + p_pitch, -89.f, 89.f );
		_updateVectors();
	}

	void Camera::setPosition( const Vec3f & p_position )
	{
		_position = p_position;
		_computeViewMatrix();
	}

	void Camera::setLookAt( const Vec3f & p_lookAt )
	{
		_invDirection = Vec3f( p_lookAt.x, p_lookAt.y, -p_lookAt.z);
		_computeViewMatrix();
	}

	void Camera::setFovy( const float p_fovy )
	{
		_fovy = p_fovy;
		_computeProjectionMatrix();
	}

	void Camera::_computeViewMatrix()
	{ 
		_viewMatrix = glm::lookAt( _position, _invDirection, Vec3f( 0.0, 1.0, 0.0 ) );
	}

	void Camera::_computeProjectionMatrix()
	{
		_projectionMatrix = glm::perspective( _fovy, _aspectRatio, _zNear, _zFar );
	}

	void Camera::_updateVectors()
	{
		const float yaw	  = glm::radians( _yaw );
		const float pitch = glm::radians( _pitch );
		_invDirection	  = glm::normalize(
			Vec3f( glm::cos( yaw ) * glm::cos( pitch ), glm::sin( pitch ), glm::sin( yaw ) * glm::cos( pitch ) ) );
		_right = glm::normalize( glm::cross( Vec3f( 0.f, 1.f, 0.f ), _invDirection ) ); // We suppose 'y' as up.
		_up	   = glm::normalize( glm::cross( _invDirection, _right ) );

		_computeViewMatrix();
	}

} // namespace M3D_ISICG
