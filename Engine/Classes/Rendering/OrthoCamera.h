#pragma once

#include "CoreMinimal.h"
#include "Math\CoreMath.hpp"

inline namespace MARS
{
	class OrthographicCamera
	{
	public:

		OrthographicCamera(float Left, float Right, float Top, float Bottom);
		OrthographicCamera(const OrthoGraphicMatrix& InMatrix);

		void SetWorldPosition(const glm::vec3& NewPostion);
		void SetWorldRotation(const float& NewRotation);

		FORCEINLINE const glm::vec3& GetWorldPosition() const { return CurrentPosition; }
		FORCEINLINE const float& GetWorldRotation() const { return CurrentRotation; }
		FORCEINLINE const glm::mat4& GetProjectionMatrix() const { return ProjectionMatrix; }
		FORCEINLINE const glm::mat4& GetViewProjectionMatrix() const { return ProjectionViewMatrix; }
		FORCEINLINE const glm::mat4& GetViewMatrix() const { return ViewMatrix; }

	private:

		void RecalculateViewMatrix();

		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionViewMatrix;

		glm::vec3 CurrentPosition = { 0.f, 0.f, 0.f };
		float CurrentRotation = 0.f;
	};
}