// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CowerDefensePR/CowerDefensePRGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCowerDefensePRGameModeBase() {}
// Cross Module References
	COWERDEFENSEPR_API UClass* Z_Construct_UClass_ACowerDefensePRGameModeBase_NoRegister();
	COWERDEFENSEPR_API UClass* Z_Construct_UClass_ACowerDefensePRGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_CowerDefensePR();
// End Cross Module References
	void ACowerDefensePRGameModeBase::StaticRegisterNativesACowerDefensePRGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACowerDefensePRGameModeBase);
	UClass* Z_Construct_UClass_ACowerDefensePRGameModeBase_NoRegister()
	{
		return ACowerDefensePRGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ACowerDefensePRGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACowerDefensePRGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_CowerDefensePR,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACowerDefensePRGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "CowerDefensePRGameModeBase.h" },
		{ "ModuleRelativePath", "CowerDefensePRGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACowerDefensePRGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACowerDefensePRGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACowerDefensePRGameModeBase_Statics::ClassParams = {
		&ACowerDefensePRGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ACowerDefensePRGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACowerDefensePRGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACowerDefensePRGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ACowerDefensePRGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACowerDefensePRGameModeBase.OuterSingleton, Z_Construct_UClass_ACowerDefensePRGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACowerDefensePRGameModeBase.OuterSingleton;
	}
	template<> COWERDEFENSEPR_API UClass* StaticClass<ACowerDefensePRGameModeBase>()
	{
		return ACowerDefensePRGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACowerDefensePRGameModeBase);
	struct Z_CompiledInDeferFile_FID_CowerDefensePR_Source_CowerDefensePR_CowerDefensePRGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CowerDefensePR_Source_CowerDefensePR_CowerDefensePRGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACowerDefensePRGameModeBase, ACowerDefensePRGameModeBase::StaticClass, TEXT("ACowerDefensePRGameModeBase"), &Z_Registration_Info_UClass_ACowerDefensePRGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACowerDefensePRGameModeBase), 299871940U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CowerDefensePR_Source_CowerDefensePR_CowerDefensePRGameModeBase_h_3158974712(TEXT("/Script/CowerDefensePR"),
		Z_CompiledInDeferFile_FID_CowerDefensePR_Source_CowerDefensePR_CowerDefensePRGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_CowerDefensePR_Source_CowerDefensePR_CowerDefensePRGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
