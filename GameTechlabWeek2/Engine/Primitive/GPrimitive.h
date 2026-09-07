#pragma once

#include "Engine/Primitive/FMeshResource.h"

class GDevice;

class GPrimitive
{
public:
	static void Initialize(GDevice* Device);

	static FMeshResource* GetCube() { return &Cube; }
	static FMeshResource* GetSphere() { return &Sphere; }
	static FMeshResource* GetPlane() { return &Plane; }
	static FMeshResource* GetCylinder() { return &Cylinder; }
	static FMeshResource* GetCone() { return &Cone; }
	static FMeshResource* GetLine() { return &Line; }

private:

	static inline FMeshResource Cube;
	static inline FMeshResource Sphere;
	static inline FMeshResource Plane;
	static inline FMeshResource Cylinder;
	static inline FMeshResource Cone;
	static inline FMeshResource Line;
};