#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Renderer/RenderTarget.hpp>



namespace
{
	static uth::Shader batchShader;
}

namespace uth
{

	SpriteBatch::SpriteBatch(const bool adoptPointers)
		: m_atlas(nullptr),
		  m_texture(nullptr),
		  m_adoptedPointers(adoptPointers)
	{
		
	}

	SpriteBatch::~SpriteBatch()
	{
		Clear();
	}



	void SpriteBatch::AddSprite(Transform* object, const std::string& atlasName, const umath::vector4& color, const umath::rectangle& texCoords)
	{
		if ((!m_atlas && !m_texture) || !object)
		{
            if (m_adoptedPointers)
            {
                // There's no penalty for deleting a null pointer.
                delete object;
            }

			return;
		}

		unsigned short mod = static_cast<unsigned short>(m_objects.size()) * 4;

		m_objects.emplace_back(object);

		umath::rectangle tex;
		if(texCoords.width != 0 && texCoords.height != 0)
			tex = texCoords;
		else
			tex = (atlasName.empty() || !m_atlas) ? umath::rectangle(0.f, 0.f, 1.f, 1.f) : m_atlas->getTextureCoords(atlasName.c_str());


		float width = ((m_atlas ? m_atlas->GetSize().x : m_texture->GetSize().x) * tex.width),
			height = ((m_atlas ? m_atlas->GetSize().y : m_texture->GetSize().y) * tex.height);

		m_vertexData.push_back(Vertex(
			umath::vector3(-width / 2.f, -height / 2.f, 1.f),
			umath::vector2(tex.x, 1.f - tex.y),
			color
			));
		m_vertexData.push_back(Vertex(
			umath::vector3(width / 2.f, -height / 2.f, 1.f),
			umath::vector2(tex.getRight(), 1.f - tex.y),
			color
			));
		m_vertexData.push_back(Vertex(
			umath::vector3(-width / 2.f, height / 2.f, 1.f),
			umath::vector2(tex.x, 1.f - (tex.y + tex.height)),
			color
			));
		m_vertexData.push_back(Vertex(
			umath::vector3(width / 2.f, height / 2.f, 1.f),
			umath::vector2(tex.getRight(), 1.f - (tex.y + tex.height)),
			color
			));
		m_spriteBuffer.addIndex(0 + mod);
		m_spriteBuffer.addIndex(1 + mod);
		m_spriteBuffer.addIndex(2 + mod);
		m_spriteBuffer.addIndex(1 + mod);
		m_spriteBuffer.addIndex(3 + mod);
		m_spriteBuffer.addIndex(2 + mod);
	}

	void SpriteBatch::SetTextureAtlas(TextureAtlas* atlas)
	{
		m_atlas = atlas;
		m_texture = nullptr;
	}

	void SpriteBatch::SetTexture(Texture* texture)
	{
		m_texture = texture;
		m_atlas = nullptr;
	}

	void SpriteBatch::Clear()
	{
		if (!m_adoptedPointers)
		{
			for (auto& i : m_objects)
				i.release();
		}

		m_objects.clear();
		m_vertexData.clear();
		m_spriteBuffer.clear();
	}

	void SpriteBatch::draw(RenderTarget& target)
	{
		if ((!m_atlas && !m_texture) || m_objects.empty())
			return;

		static bool shaderLoaded = false;
		if (!shaderLoaded)
		{
			batchShader.LoadShader("Shaders/batchvertexshader.vert", "Shaders/batchfragmentshader.frag");
			shaderLoaded = true;
		}

		m_spriteBuffer.clear(true, false);
		m_spriteBuffer.addVertices(m_vertexData);

		for (size_t i = 0; i < m_vertexData.size() / 4; ++i)
		{
			umath::matrix3 m = m_objects[i]->GetTransform().getMatrix3();
			// NOTE: this will cause the map to draw correctly.
			// TODO: figure out a real solution
			//m[0][0] = m[0][0] > 0 ? 1 : -1;
			//m[1][1] = m[1][1] > 0 ? 1 : -1;

			m_spriteBuffer.m_vertexData[0 + (i * 4)].position *= m;
			m_spriteBuffer.m_vertexData[1 + (i * 4)].position *= m;
			m_spriteBuffer.m_vertexData[2 + (i * 4)].position *= m;
			m_spriteBuffer.m_vertexData[3 + (i * 4)].position *= m;
		}

		m_spriteBuffer.setData();

		m_atlas ? m_atlas->Bind() : m_texture->Bind();

		batchShader.Use();

		batchShader.SetUniform("unifProjection", target.GetCamera().GetProjectionTransform());
		batchShader.SetUniform("unifSampler", 0);
		//batchShader.SetUniform("unifColor", 1, 1, 1, 1);


		uth::Graphics::BindBuffer(ARRAY_BUFFER, m_spriteBuffer.m_arrayBuffer);
		batchShader.setAttributeData("attrPosition", 3, FLOAT_TYPE, sizeof(Vertex), (void*)0);
		batchShader.setAttributeData("attrUV", 2, FLOAT_TYPE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		batchShader.setAttributeData("attrColor", 4, FLOAT_TYPE, sizeof(Vertex), (void*)(5 * sizeof(float)));

		uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_spriteBuffer.m_elementBuffer);
		uth::Graphics::DrawElements(TRIANGLES, m_spriteBuffer.getIndices().size(), UNSIGNED_SHORT_TYPE, (void*)0);

		target.SetShader(nullptr);
	}
}