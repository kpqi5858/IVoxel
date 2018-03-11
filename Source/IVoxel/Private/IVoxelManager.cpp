#include "IVoxelManager.h"


IVoxelManager::IVoxelManager(ATestActor* World, uint8 OctreeDepth) 
	: World(World), MainOctree(new FOctree(FIntVector(0), OctreeDepth))
{

}

IVoxelManager::~IVoxelManager()
{
	MainOctree->Destroy();
	delete MainOctree;
}

void IVoxelManager::Tick()
{

}

void IVoxelManager::PolygonizeOctree(FVector OctreeLocation, uint8 RenderSize, uint8 RenderDepth)
{
	FOctree* Chunk = MainOctree->GetOctree(OctreeLocation, RenderSize);
	TSet<FOctree*> Octrees;
	Chunk->GetChildOctrees(Octrees, RenderDepth);

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FRuntimeMeshTangent> Tangent;
	TArray<FColor> VertexColor;
	for (auto& Octree : Octrees)
	{
		if (Octree->GetValue())
		{
			URuntimeMeshShapeGenerator::CreateBoxMesh(Octree->Size(), FVector(Octree->Position), Octree->GetColor(), Vertices, Triangles, Normals, UVs, Tangent, VertexColor);
		}
	}
	World->RMC->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColor, Tangent, true);
}

void IVoxelManager::MakeCube(int Radius, FVector Location, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals)
{
	int offset = Vertices.Num();

	FVector Vert[8];
	Vert[0] = FVector(+Radius, +Radius, +Radius) + Location;
	Vert[1] = FVector(-Radius, +Radius, +Radius) + Location;
	Vert[2] = FVector(+Radius, -Radius, +Radius) + Location;
	Vert[3] = FVector(-Radius, -Radius, +Radius) + Location;
	Vert[4] = FVector(+Radius, +Radius, -Radius) + Location;
	Vert[5] = FVector(-Radius, +Radius, -Radius) + Location;
	Vert[6] = FVector(+Radius, -Radius, -Radius) + Location;
	Vert[7] = FVector(-Radius, -Radius, -Radius) + Location;

	//Up
	Vertices.Add(Vert[0]);
	Vertices.Add(Vert[1]);
	Vertices.Add(Vert[2]);
	Vertices.Add(Vert[3]);
	Normals.Add(FVector(0, 0, 1));
	Normals.Add(FVector(0, 0, 1));
	Normals.Add(FVector(0, 0, 1));
	Normals.Add(FVector(0, 0, 1));
	Triangles.Add(0 + offset);
	Triangles.Add(3 + offset);
	Triangles.Add(1 + offset);
	Triangles.Add(0 + offset);
	Triangles.Add(2 + offset);
	Triangles.Add(3 + offset);
}