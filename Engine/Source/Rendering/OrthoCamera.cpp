#include "Rendering/OrthoCamera.h"
#include "glm/ext/matrix_clip_space.hpp"

MARS::OrthographicCamera::OrthographicCamera(float Left, float Right, float Top, float Bottom)
	: ProjectionMatrix(glm::ortho(Left, Right, Bottom, Top, -1.f, 1.f)), ViewMatrix(1.f)
{
	ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;
}

MARS::OrthographicCamera::OrthographicCamera(const OrthoGraphicMatrix& InMatrix)
{
	Unimplemented()
}

void MARS::OrthographicCamera::SetWorldPosition(const glm::vec3& NewPostion)
{
	CurrentPosition = NewPostion;
	RecalculateViewMatrix();
}

void MARS::OrthographicCamera::SetWorldRotation(const float& NewRotation)
{
	CurrentRotation = NewRotation;
	RecalculateViewMatrix();
}

void MARS::OrthographicCamera::RecalculateViewMatrix()
{
	glm::mat4 Transform	 =	glm::translate(glm::mat4(1.f), CurrentPosition) * glm::rotate(glm::mat4(1.f), 
							glm::radians(CurrentRotation), glm::vec3(0, 0, 1));
	ViewMatrix = glm::inverse(Transform);
	ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;
}