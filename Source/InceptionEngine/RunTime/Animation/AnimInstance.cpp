#include "IE_PCH.h"

#include "AnimInstance.h"
#include "Animation.h"
#include "RunTime/Resource/ResourceManager.h"
#include "ECS/Components/AnimationComponent/EventAnimPlaySetting.h"

namespace inceptionengine
{
	AnimInstance::AnimInstance(std::string const& animFilePath)
	{
		std::shared_ptr<Animation> pAnimation = gResourceMgr.GetResource<Animation>(animFilePath);
		assert(pAnimation != nullptr);
		mAnimationResource = pAnimation;
		mAnimationFilePath = animFilePath;
	}

	AnimInstance::AnimInstance(EventAnimPlaySetting const& setting)
	{
		std::shared_ptr<Animation> pAnimation = gResourceMgr.GetResource<Animation>(setting.animFilePath);
		assert(pAnimation != nullptr);
		mAnimationResource = pAnimation;
		mAnimationFilePath = setting.animFilePath;

		mRootMotion = setting.rootMotion;
		mBlendInDuration = setting.blendInDuration;
		mBlendOutDuration = setting.blendOutDuration;

		mAnimSpeedBar.AddAnimSpeedRanges(setting.animSpeedRanges);

		mAnimStartCallback = setting.animStartCallback;
		mAnimInterruptCallback = setting.animInterruptCallback;
		mAnimEndCallback = setting.animEndCallback;
		mAnimBlendOutFinishCallback = setting.animBlendOutFinishCallback;

		for (AnimNotify const& notify : setting.animNotifies)
		{
			mAnimNotifies.push_back(notify);
		}

		mAnimNotifies.sort([](AnimNotify const& lhs, AnimNotify const& rhs) -> bool { return lhs.ratio < rhs.ratio; });

		mAnimNotifyStates = setting.animNotifyStates;
	}

	AnimInstance::~AnimInstance() = default;

	AnimPose AnimInstance::Sample(float time, AnimInterpType interpType)
	{
		return mAnimationResource->Interpolate(time);
	}

	float AnimInstance::GetDuration() const
	{
		return mAnimationResource->GetDuration();
	}

	void AnimInstance::Start()
	{
		mAnimStartCallback();
	}

	void AnimInstance::End()
	{
		mAnimEndCallback();
	}

	void AnimInstance::Interrupt()
	{
		mAnimInterruptCallback();
	}

	float AnimInstance::QueryAnimSpeed(float ratio) const
	{
		return mAnimSpeedBar.QueryAnimSpeed(ratio);
	}


	float AnimInstance::GetBlendOutDuration() const
	{
		return mBlendOutDuration;
	}
	void AnimInstance::InsertAnimSpeedRange(AnimSpeedRange const& range)
	{
		mAnimSpeedBar.InsertAnimSpeedRange(range);
	}
}

