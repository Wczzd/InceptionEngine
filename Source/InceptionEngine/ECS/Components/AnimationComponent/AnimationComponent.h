#pragma once
#include "EngineGlobals/EngineApiPrefix.h"
#include "ECS/Entity/EntityID.h"
#include "RunTime/Animation/AnimationController.h"
#include "AnimStateMachine.h"

namespace inceptionengine
{
	class Entity;
	class World;
	class AnimationController;

	class IE_API AnimationComponent
	{
	public:
		AnimationComponent(EntityID entityID, std::reference_wrapper<World> world);
		~AnimationComponent();

		AnimationComponent(AnimationComponent const&) = delete;

		AnimationComponent(AnimationComponent&&) noexcept;



		void PlayAnimation(std::string const& filePath);

		void HandReachTarget(Matrix4x4f const& EndEffector);

		void TestAxis();

		void StopAnimation();

		bool IsPlayingAnimation();

		template<typename T>
		void SetAnimStateMachine()
		{
			mAnimationController->SetAnimStateMachine<T>(mEntityID, mWorld);
		}

	private:
		friend class AnimationSystem;
		friend class SkeletalMeshComponent;
		friend class SkeletalMeshRenderSystem;

		std::unique_ptr<AnimationController> mAnimationController = nullptr;
		EntityID mEntityID = InvalidEntityID;
		std::reference_wrapper<World> mWorld;

	};
}