/**
* @file		FbxRelated.cpp
* @brief	FbxRelatedクラス実装
* @author	kawaguchi
*/

#include "FbxRelated.h"

FbxRelated::FbxRelated()
{
	m_pFbxManager	= NULL;
	m_pFbxScene		= NULL;
	m_pModel = new FbxModel;
	m_pModel->m_pFbxModelData = new FbxModel::FbxModelData;
}

FbxRelated::~FbxRelated()
{
	Release();
}

void FbxRelated::Release()
{
	if (m_pFbxScene)
	{
		m_pFbxScene->Destroy();
		m_pFbxScene = NULL;
	}

	if (m_pFbxManager)
	{
		m_pFbxManager->Destroy();
		m_pFbxManager = NULL;
	}
	/*
	if (!m_pModel->m_pFbxModelData->pVertexColor)
	{
		delete m_pModel->m_pFbxModelData->pVertexColor;
	}
	*/
	for (int i = 0; i < m_pModel->m_pFbxModelData->UvLayerCount; i++)
	{
		delete m_pModel->m_pFbxModelData->uvSet.uvBuffer[i];
	}

	if (m_pModel->m_pFbxModelData->fileTextureCount)
	{
		delete m_pModel->m_pFbxModelData->pTmpTexture;
	}
	delete m_pModel->m_pFbxModelData->pIndexBuffer;
	delete m_pModel->m_pFbxModelData->pVertex;
	delete m_pModel->m_pFbxModelData->pPolygonSize;
	delete m_pModel->m_pFbxModelData;
	delete m_pModel;
}


void FbxRelated::TriangulateRecursive(FbxNode* pNode, FbxScene* pScene)
{
	FbxNodeAttribute* pNodeAttribute = pNode->GetNodeAttribute();

	if (pNodeAttribute)
	{
		FbxNodeAttribute::EType type = pNodeAttribute->GetAttributeType();
		if (type == FbxNodeAttribute::eMesh ||
			type == FbxNodeAttribute::eNurbs ||
			type == FbxNodeAttribute::eNurbsSurface ||
			type == FbxNodeAttribute::ePatch)
		{
			FbxGeometryConverter lConverter(pNode->GetFbxManager());
			if (lConverter.Triangulate(pScene, true) == false)
			{
				MessageBox(NULL, TEXT("三角形化に失敗しました。"), TEXT("エラー"), MB_OK);
			}
		}
	}

	const int lChildCount = pNode->GetChildCount();
	for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
	{
		// 子ノードを探索。 
		TriangulateRecursive(pNode->GetChild(lChildIndex), pScene);
	}
}

bool FbxRelated::InitializeFbxSdkObjects()
{
	m_pFbxManager = fbxsdk::FbxManager::Create();

	if (!m_pFbxManager)
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		return false;
	}
	else
	{
		FBXSDK_printf("Autodesk FBX SDK version %s\n", m_pFbxManager->GetVersion());
	}

	fbxsdk::FbxIOSettings* pIOSetting = fbxsdk::FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	m_pFbxManager->SetIOSettings(pIOSetting);

	m_pFbxScene = fbxsdk::FbxScene::Create(m_pFbxManager, "");
	if (!m_pFbxScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		return false;
	}
	return true;
}

bool FbxRelated::LoadFbx(const char* pName)
{

	int sFileFormat = -1;

	// FBX SDK オブジェクトの初期化。 
	if (!InitializeFbxSdkObjects())
	{
		return false;
	}

	// インポータ作成。 
	fbxsdk::FbxImporter* m_pFbxImporter;

	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	if (!m_pFbxImporter)
	{
		FBXSDK_printf("Error: Unable to create FBX importer!\n");
		return false;
	}

	// ファイルを指定したインポート(リーダー)ファイル形式で検出します。 
	if (!m_pFbxManager->GetIOPluginRegistry()->DetectReaderFileFormat(pName, sFileFormat))
	{
		// 検出できないファイル形式です。 FbxImporter::eFBX_BINARY 形式でトライします。 
		sFileFormat = m_pFbxManager->GetIOPluginRegistry()->FindReaderIDByDescription("FBX binary (*.fbx)");
	}

	// FBXファイルを読み込む。 
	if (!m_pFbxImporter->Initialize(pName, sFileFormat))
	{
		FBXSDK_printf("Error: Unable to create FBX initialize!\n");
		return false;
	}

	// 読み込んだFBXファイルからシーンデータを取り出す。 
	if (!m_pFbxImporter->Import(m_pFbxScene))
	{
		FBXSDK_printf("Error: Unable to create FBX import!\n");
		return false;
	}

	m_pFbxImporter->Destroy();
	m_pFbxImporter = NULL;

	// 三角形化(データによっては、四角形ポリゴンとか混ざっている場合がある) 
	TriangulateRecursive(m_pFbxScene->GetRootNode(), m_pFbxScene);
	
	//	ルートノードを取得
	fbxsdk::FbxNode* pRootNode = m_pFbxScene->GetRootNode();

	if (NULL != pRootNode)
	{
		//	ルートノードの子ノード数を取得
		int childCount = pRootNode->GetChildCount();

		//	子ノードの数だけ探査をする
		for (int i = 0; childCount > i; i++)
		{
			GetMesh(pRootNode->GetChild(i));
		}
	}
	return true;

}


void FbxRelated::GetMesh(fbxsdk::FbxNode* pNode)
{	
	//	ノードも属性を取得
	fbxsdk::FbxNodeAttribute* pAttr = pNode->GetNodeAttribute();

	if (NULL != pAttr)
	{
		//	属性の判別
		switch (pAttr->GetAttributeType())
		{
			//	メッシュノード発見
		case fbxsdk::FbxNodeAttribute::eMesh:
		{
			fbxsdk::FbxMesh* pMesh = pNode->GetMesh();
			GetPosition(pMesh);

			//	頂点の法線座標を取得
			GetVertexNormal(pMesh);

			//	UV座標を取得
			GetVertexUV(pMesh);

			//	マテリアルとテクスチャ名を取得
			GetMaterialData(pMesh);

			//	頂点カラーを取得
//			GetVertexColor(pMesh);
		}
		break;
		}
	}

	//	子ノードの再起探査
	int childCount = pNode->GetChildCount();

	for (int i = 0; childCount > i; i++)
	{
		GetMesh(pNode->GetChild(i));
	}
}

void FbxRelated::GetPosition(fbxsdk::FbxMesh* pMesh)
{
	//	ポリゴン数を取得
	m_pModel->m_pFbxModelData->polygonCount = pMesh->GetPolygonCount();

	//	ポリゴンサイズを取得
	m_pModel->m_pFbxModelData->pPolygonSize = new int[m_pModel->m_pFbxModelData->polygonCount];

	for (int i = 0; m_pModel->m_pFbxModelData->polygonCount > i; i++)
	{
		m_pModel->m_pFbxModelData->pPolygonSize[i] = pMesh->GetPolygonSize(i);
	}

	//	総頂点数を取得
	m_pModel->m_pFbxModelData->vertexCount = pMesh->GetControlPointsCount();

	//	インデックス数を取得
	m_pModel->m_pFbxModelData->indexCount = pMesh->GetPolygonVertexCount();

	//	頂点バッファの取得
	fbxsdk::FbxVector4* pVertex = pMesh->GetControlPoints();

	//	インデックスバッファの取得
	int* pIndex = pMesh->GetPolygonVertices();

	//	頂点座標のキャストとハードコピー
	D3DXVECTOR3* pTmpVertex = new D3DXVECTOR3[m_pModel->m_pFbxModelData->vertexCount];

	for (int i = 0; m_pModel->m_pFbxModelData->vertexCount > i; i++)
	{
		//	i番目の頂点の座標Xを取得
		pTmpVertex[i].x = (float)pVertex[i][0];

		if (m_pModel->maxX < pTmpVertex[i].x)
		{
			m_pModel->maxX = pTmpVertex[i].x;
		}
		if (m_pModel->minX > pTmpVertex[i].x)
		{
			m_pModel->minX = pTmpVertex[i].x;
		}

		//	i番目の頂点の座標Yを取得
		pTmpVertex[i].y = (float)pVertex[i][1];

		if (m_pModel->maxY < pTmpVertex[i].y)
		{
			m_pModel->maxY = pTmpVertex[i].y;
		}
		if (m_pModel->minY > pTmpVertex[i].y)
		{
			m_pModel->minY = pTmpVertex[i].y;
		}

		//	i番目の頂点の座標Zを取得
		pTmpVertex[i].z = (float)pVertex[i][2];
	
		if (m_pModel->maxZ < pTmpVertex[i].z)
		{
			m_pModel->maxZ = pTmpVertex[i].z;
		}
		if (m_pModel->minZ > pTmpVertex[i].z)
		{
			m_pModel->minZ = pTmpVertex[i].z;
		}

		if (m_pModel->maxR < pTmpVertex[i].x)
		{
			m_pModel->maxR = pTmpVertex[i].x;
		}
		if (m_pModel->maxR < pTmpVertex[i].y)
		{
			m_pModel->maxR = pTmpVertex[i].y;
		}
		if (m_pModel->maxR < pTmpVertex[i].z)
		{
			m_pModel->maxR = pTmpVertex[i].z;
		}
	}

	m_pModel->m_pFbxModelData->pVertex = new FbxModel::Vertex[m_pModel->m_pFbxModelData->indexCount];

	for (int i = 0; m_pModel->m_pFbxModelData->indexCount > i; i++)
	{
		//	i番目の頂点の座標Xを取得
		m_pModel->m_pFbxModelData->pVertex[i].Vec.x = pTmpVertex[pIndex[i]].x;

		//	i番目の頂点の座標Yを取得
		m_pModel->m_pFbxModelData->pVertex[i].Vec.y = pTmpVertex[pIndex[i]].y;

		//	i番目の頂点の座標Zを取得
		m_pModel->m_pFbxModelData->pVertex[i].Vec.z = pTmpVertex[pIndex[i]].z;
	}
	
	//	インデックスバッファのハードコピー
	m_pModel->m_pFbxModelData->pIndexBuffer = new int[m_pModel->m_pFbxModelData->indexCount];

	for (int i = 0; m_pModel->m_pFbxModelData->indexCount > i; i++)
	{
		m_pModel->m_pFbxModelData->pIndexBuffer[i] = pIndex[i];
	}
	delete pTmpVertex;
}

void FbxRelated::GetVertexNormal(fbxsdk::FbxMesh* pMesh)
{
	//	法線セット数を取得
	int normalLayerCount = pMesh->GetElementNormalCount();

	//	レイヤー数だけ回る
	for (int i = 0; normalLayerCount > i; i++)
	{
		//	法線セットを取得
		fbxsdk::FbxGeometryElementNormal* pNormal = pMesh->GetElementNormal(i);

		//	マッピングモードの取得
		fbxsdk::FbxGeometryElement::EMappingMode mapping = pNormal->GetMappingMode();

		//	リファレンスモードの取得
		fbxsdk::FbxGeometryElement::EReferenceMode reference = pNormal->GetReferenceMode();

		//	マッピングモードの判別
		switch (mapping)
		{
		case fbxsdk::FbxGeometryElement::eByControlPoint:

			//	リファレンスモードの判別
			switch (reference)
			{
			case fbxsdk::FbxGeometryElement::eDirect:
			{
				//	法線数を取得
				int normalCount = pNormal->GetDirectArray().GetCount();

				//	eDirect の場合データは順番に格納されているのでそのまま保持
				for (int i = 0; normalCount > i; i++)
				{
					//	法線の取得
					m_pModel->m_pFbxModelData->pVertex[i].Normal.x = (float)pNormal->GetDirectArray().GetAt(i)[0];
					m_pModel->m_pFbxModelData->pVertex[i].Normal.y = (float)pNormal->GetDirectArray().GetAt(i)[1];
					m_pModel->m_pFbxModelData->pVertex[i].Normal.z = (float)pNormal->GetDirectArray().GetAt(i)[2];
				}
			}
			break;

			case fbxsdk::FbxGeometryElement::eIndexToDirect:
				break;

			default:
				break;
			}

			break;

		case fbxsdk::FbxGeometryElement::eByPolygonVertex:
			//	リファレンスモードの判別
			switch (reference)
			{
			case fbxsdk::FbxGeometryElement::eDirect:
			{
				//	法線数を取得
				int normalCount = pNormal->GetDirectArray().GetCount();

				//	eDirect の場合データは順番に格納されているのでそのまま保持
				for (int i = 0; normalCount > i; i++)
				{
					//	法線の取得
					m_pModel->m_pFbxModelData->pVertex[i].Normal.x = (float)pNormal->GetDirectArray().GetAt(i)[0];
					m_pModel->m_pFbxModelData->pVertex[i].Normal.y = (float)pNormal->GetDirectArray().GetAt(i)[1];
					m_pModel->m_pFbxModelData->pVertex[i].Normal.z = (float)pNormal->GetDirectArray().GetAt(i)[2];
				}
			}
			break;

			case fbxsdk::FbxGeometryElement::eIndexToDirect:
				break;

			default:
				break;
			}

			break;


			break;

		default:
			break;
		}
	}
}


//	UV取得関数
void FbxRelated::GetVertexUV(fbxsdk::FbxMesh* pMesh)
{
	//	UVセット数を取得
	m_pModel->m_pFbxModelData->UvLayerCount = pMesh->GetElementUVCount();

	for (int i = 0; m_pModel->m_pFbxModelData->UvLayerCount > i; i++)
	{
		//	UVバッファを取得
		fbxsdk::FbxGeometryElementUV* pUV = pMesh->GetElementUV(i);

		//	マッピングモードの取得
		fbxsdk::FbxGeometryElement::EMappingMode mapping = pUV->GetMappingMode();

		//	リファレンスモードの取得
		fbxsdk::FbxGeometryElement::EReferenceMode reference = pUV->GetReferenceMode();

		//	UV数を取得
		int uvCount = pUV->GetDirectArray().GetCount();

		//	マッピングモードの判別
		switch (mapping)
		{
		case fbxsdk::FbxGeometryElement::eByControlPoint:
			break;

		case fbxsdk::FbxGeometryElement::eByPolygonVertex:

			//	リファレンスモードの判別
			switch (reference)
			{
			case fbxsdk::FbxGeometryElement::eDirect:
				break;

			case fbxsdk::FbxGeometryElement::eIndexToDirect:
			{
				fbxsdk::FbxLayerElementArrayTemplate<int>* pUvIndex = &pUV->GetIndexArray();

				m_pModel->m_pFbxModelData->uvIndexCount = pUvIndex->GetCount();

				//	UVを保持
				std::vector<D3DXVECTOR2*> temp;
				temp.push_back(new D3DXVECTOR2[m_pModel->m_pFbxModelData->uvIndexCount]);

				for (int j = 0; m_pModel->m_pFbxModelData->uvIndexCount > j; j++)
				{
					temp[i][j].x = (float)pUV->GetDirectArray().GetAt(pUvIndex->GetAt(j))[0];
					temp[i][j].y = 1.f - (float)pUV->GetDirectArray().GetAt(pUvIndex->GetAt(j))[1];
					m_pModel->m_pFbxModelData->uvSet.uvBuffer.push_back(temp[i]);
				}

				//	UVSet名を取得
				m_pModel->m_pFbxModelData->uvSet.uvSetName = pUV->GetName();
			}
			break;

			default:
				break;
			}
			break;

		case fbxsdk::FbxGeometryElement::eByEdge:
			break;

		case fbxsdk::FbxGeometryElement::eByPolygon:
			break;

		default:
			break;
		}
	}
	for (int i = 0; i < m_pModel->m_pFbxModelData->indexCount; i++)
	{
		m_pModel->m_pFbxModelData->pVertex[i].tu = m_pModel->m_pFbxModelData->uvSet.uvBuffer[0][i].x;
		m_pModel->m_pFbxModelData->pVertex[i].tv = m_pModel->m_pFbxModelData->uvSet.uvBuffer[0][i].y;
	}
	
}


void FbxRelated::GetMaterialData(fbxsdk::FbxMesh* pMesh)
{
	//	メッシュからノードを取得
	fbxsdk::FbxNode* pNode = pMesh->GetNode();

	//	マテリアルの数を取得
	m_pModel->m_pFbxModelData->materialCount = pNode->GetMaterialCount();

	//	テクスチァの数をカウントする
	static int fileTextureCount = 0;

	//	マテリアルの数だけ繰り返す
	for (int i = 0; m_pModel->m_pFbxModelData->materialCount > i; i++)
	{
		//	マテリアルを取得
		fbxsdk::FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		D3DMATERIAL9 MaterialData;

		if (pMaterial->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId))
		{
			// Lambertにダウンキャスト
			fbxsdk::FbxSurfaceLambert* lambert = (fbxsdk::FbxSurfaceLambert*)pMaterial;

			// アンビエント
			MaterialData.Ambient.r = (float)lambert->Ambient.Get().mData[0] * (float)lambert->AmbientFactor.Get();
			MaterialData.Ambient.g = (float)lambert->Ambient.Get().mData[1] * (float)lambert->AmbientFactor.Get();
			MaterialData.Ambient.b = (float)lambert->Ambient.Get().mData[2] * (float)lambert->AmbientFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sAmbient);

			// ディフューズ
			MaterialData.Diffuse.r = (float)lambert->Diffuse.Get().mData[0] * (float)lambert->DiffuseFactor.Get();
			MaterialData.Diffuse.g = (float)lambert->Diffuse.Get().mData[1] * (float)lambert->DiffuseFactor.Get();
			MaterialData.Diffuse.b = (float)lambert->Diffuse.Get().mData[2] * (float)lambert->DiffuseFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sDiffuse);

			// エミッシブ
			MaterialData.Emissive.r = (float)lambert->Emissive.Get().mData[0] * (float)lambert->EmissiveFactor.Get();
			MaterialData.Emissive.g = (float)lambert->Emissive.Get().mData[1] * (float)lambert->EmissiveFactor.Get();
			MaterialData.Emissive.b = (float)lambert->Emissive.Get().mData[2] * (float)lambert->EmissiveFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sEmissive);

			// 透過度
			MaterialData.Ambient.a = 0.f;
			MaterialData.Diffuse.a = 1.f;
			MaterialData.Emissive.a = 0.f;
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sTransparentColor);


			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sNormalMap);

			m_pModel->m_pFbxModelData->MaterialData.push_back(MaterialData);
		}
		else if (pMaterial->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
		{
			// Phongにダウンキャスト
			fbxsdk::FbxSurfacePhong* phong = (fbxsdk::FbxSurfacePhong*)pMaterial;

			// アンビエント
			MaterialData.Ambient.r = (float)phong->Ambient.Get().mData[0] * (float)phong->AmbientFactor.Get();
			MaterialData.Ambient.g = (float)phong->Ambient.Get().mData[1] * (float)phong->AmbientFactor.Get();
			MaterialData.Ambient.b = (float)phong->Ambient.Get().mData[2] * (float)phong->AmbientFactor.Get();
			GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sAmbient);

			// ディフューズ
			MaterialData.Diffuse.r = (float)phong->Diffuse.Get().mData[0] * (float)phong->DiffuseFactor.Get();
			MaterialData.Diffuse.g = (float)phong->Diffuse.Get().mData[1] * (float)phong->DiffuseFactor.Get();
			MaterialData.Diffuse.b = (float)phong->Diffuse.Get().mData[2] * (float)phong->DiffuseFactor.Get();
			GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sDiffuse);

			// エミッシブ
			MaterialData.Emissive.r = (float)phong->Emissive.Get().mData[0] * (float)phong->EmissiveFactor.Get();
			MaterialData.Emissive.g = (float)phong->Emissive.Get().mData[1] * (float)phong->EmissiveFactor.Get();
			MaterialData.Emissive.b = (float)phong->Emissive.Get().mData[2] * (float)phong->EmissiveFactor.Get();
			GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sEmissive);

			// 透過度
			MaterialData.Ambient.a = 0.f;
			MaterialData.Diffuse.a = 1.f;
			MaterialData.Emissive.a = 0.f;
			MaterialData.Specular.a = 0.f;
			GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sTransparentColor);

			// スペキュラ
			MaterialData.Specular.r = (float)phong->Specular.Get().mData[0] * (float)phong->SpecularFactor.Get();
			MaterialData.Specular.g = (float)phong->Specular.Get().mData[1] * (float)phong->SpecularFactor.Get();
			MaterialData.Specular.b = (float)phong->Specular.Get().mData[2] * (float)phong->SpecularFactor.Get();
			GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sSpecular);

			// 光沢
//			shininess_ = (float)phong->GetShininess().Get();		??????????????

			// 反射
//			reflectivity_ = (float)phong->GetReflectionFactor().Get();		??????????????

			MaterialData.Power = (float)phong->Shininess.Get();

			GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sNormalMap);

			m_pModel->m_pFbxModelData->MaterialData.push_back(MaterialData);
		}

	}

}

void FbxRelated::GetTextureName(fbxsdk::FbxSurfaceMaterial* pMaterial, const char* pMatAttr)
{
	//	プロパティを取得
	fbxsdk::FbxProperty prop = pMaterial->FindProperty(pMatAttr);

	//	FbxLayerTexture の数を取得
	int layeredTextureCount = prop.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

	//	アタッチされたテクスチャがFbxLayeredTexture の場合
	if (0 < layeredTextureCount)
	{
		//	アタッチされたテクスチャの数だけ繰り返す
		for (int i = 0; layeredTextureCount > i; i++)
		{
			//	テクスチャを取得
			fbxsdk::FbxLayeredTexture* pLayeredTexture = prop.GetSrcObject<fbxsdk::FbxLayeredTexture>(i);

			//	レイヤー数を取得
			int textureCount = pLayeredTexture->GetSrcObjectCount<fbxsdk::FbxFileTexture>();

			//	レイヤー数だけ繰り返す
			for (int j = 0; textureCount > j; j++)
			{
				//	テクスチャを取得
				fbxsdk::FbxFileTexture* pFbxFileTexture = prop.GetSrcObject<fbxsdk::FbxFileTexture>(j);

				if (pFbxFileTexture)
				{
					//	テクスチャ名を取得
					//	std::string textureName = texture->GetName();
					LPCSTR textureName = pFbxFileTexture->GetRelativeFileName();

					//	UVSet名を取得
					std::string UVSetName = pFbxFileTexture->UVSet.Get().Buffer();

					//	UVSet名を比較し対応しているテクスチャなら保持してデータクラスにUV座標をいれる
					if (m_pModel->m_pFbxModelData->uvSet.uvSetName == UVSetName)
					{
						m_pModel->m_pFbxModelData->pTmpTexture = new FbxModel::TextureData();
						m_pModel->m_pFbxModelData->pTmpTexture->TextureName = textureName;
						m_pModel->m_pFbxModelData->pTextureData.push_back(m_pModel->m_pFbxModelData->pTmpTexture);

						if (FAILED(D3DXCreateTextureFromFile(
							m_pModel->m_pDevice,
							m_pModel->m_pFbxModelData->pTextureData[m_pModel->m_pFbxModelData->fileTextureCount]->TextureName,
							&m_pModel->m_pFbxModelData->pTextureData[m_pModel->m_pFbxModelData->fileTextureCount]->pTexture)))
						{
							m_pModel->m_pFbxModelData->pTextureData[m_pModel->m_pFbxModelData->fileTextureCount]->pTexture = NULL;
						}
						m_pModel->m_pFbxModelData->fileTextureCount++;
					}
				}
			}
		}
	}
	else
	{
		//	テクスチャ数を取得
		int fileTextureCount = prop.GetSrcObjectCount<fbxsdk::FbxFileTexture>();

		if (0 < fileTextureCount)
		{
			//	テクスチャの数だけ繰り返す
			for (int i = 0; fileTextureCount > i; i++)
			{
				//	テクスチャを取得
				fbxsdk::FbxFileTexture* pFbxFileTexture = prop.GetSrcObject<fbxsdk::FbxFileTexture>(i);

				if (pFbxFileTexture)
				{
					//	テクスチャ名を取得
					//	std::string textureName = texture->GetName();
					LPCSTR textureName = pFbxFileTexture->GetRelativeFileName();

					//	UVSet名を取得
					std::string UVSetName = pFbxFileTexture->UVSet.Get().Buffer();

					//	UVSet名を比較し対応しているテクスチャなら保持
					if (m_pModel->m_pFbxModelData->uvSet.uvSetName == UVSetName)
					{
						m_pModel->m_pFbxModelData->pTmpTexture = new FbxModel::TextureData();
						m_pModel->m_pFbxModelData->pTmpTexture->TextureName = textureName;
						m_pModel->m_pFbxModelData->pTextureData.push_back(m_pModel->m_pFbxModelData->pTmpTexture);

						if (FAILED(D3DXCreateTextureFromFile(
							m_pModel->m_pDevice,
							m_pModel->m_pFbxModelData->pTextureData[m_pModel->m_pFbxModelData->fileTextureCount]->TextureName,
							&m_pModel->m_pFbxModelData->pTextureData[m_pModel->m_pFbxModelData->fileTextureCount]->pTexture)))
						{
							m_pModel->m_pFbxModelData->pTextureData[m_pModel->m_pFbxModelData->fileTextureCount]->pTexture = NULL;
						}
						m_pModel->m_pFbxModelData->fileTextureCount++;

					}
				}
			}
		}
	}
}
/*
void FbxRelated::GetVertexColor(fbxsdk::FbxMesh* pMesh)
{
	//	頂点カラーセット数を取得
	int vColorLayerCount = pMesh->GetElementVertexColorCount();

	//	レイヤー数だけ回る
	for (int i = 0; vColorLayerCount > i; i++)
	{
		//	法線セットを取得
		fbxsdk::FbxGeometryElementVertexColor* pColor = pMesh->GetElementVertexColor(i);

		//	マッピングモードの取得
		fbxsdk::FbxGeometryElement::EMappingMode mappingMode = pColor->GetMappingMode();

		//	リファレンスモードの取得
		fbxsdk::FbxGeometryElement::EReferenceMode referenceMode = pColor->GetReferenceMode();

		//	マッピングモードの判別
		switch (mappingMode)
		{
		case fbxsdk::FbxGeometryElement::eByControlPoint:
			break;

		case fbxsdk::FbxGeometryElement::eByPolygon:
			break;

		case fbxsdk::FbxGeometryElement::eByPolygonVertex:

			//	リファレンスモードの判別
			switch (referenceMode)
			{
			case fbxsdk::FbxGeometryElement::eIndexToDirect:
			{
				fbxsdk::FbxLayerElementArrayTemplate<int>* pIndex = &pColor->GetIndexArray();
				int indexCount = pIndex->GetCount();

				m_pModel->m_pFbxModelData->pVertexColor = new FbxModel::ColorRGBA[indexCount];

				//	頂点の数だけ頂点カラーを取得
				for (int j = 0; indexCount > j; j++)
				{
					m_pModel->m_pFbxModelData->pVertexColor[j].r = (float)pColor->GetDirectArray().GetAt(pIndex->GetAt(j))[0];
					m_pModel->m_pFbxModelData->pVertexColor[j].g = (float)pColor->GetDirectArray().GetAt(pIndex->GetAt(j))[1];
					m_pModel->m_pFbxModelData->pVertexColor[j].b = (float)pColor->GetDirectArray().GetAt(pIndex->GetAt(j))[2];
					m_pModel->m_pFbxModelData->pVertexColor[j].a = (float)pColor->GetDirectArray().GetAt(pIndex->GetAt(j))[3];
				}
			}
			break;

			case fbxsdk::FbxGeometryElement::eDirect:
				break;

			case fbxsdk::FbxGeometryElement::eIndex:
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}
*/
