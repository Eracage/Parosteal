#include <UtH/Engine/TMX/Object.hpp>

#include <tinyxml2.h>

#include <cstdlib>
#include <sstream>

using namespace uth;
using namespace TMX;

Object::Object(tinyxml2::XMLElement* objectElement)
{
    parseObject(objectElement);
}

Object::~Object()
{ }


// Public

const umath::rectangle& Object::GetRectangle() const
{
	return m_rectangle;
}

const std::vector<umath::vector2>& Object::GetPoints() const
{
	return m_points;
}

const umath::vector2 Object::GetPosition() const
{
	return umath::vector2(m_rectangle.x, m_rectangle.y);
}

std::string Object::GetProperty(const std::string& name) const
{
	auto prop = m_properties.find(name);
	if(prop != m_properties.end())
		return prop->second;

	return std::string();
}

const std::string& Object::GetName() const
{
	return m_name;
}

const std::string& Object::GetType() const
{
	return m_typeString;
}

// Private

void Object::parseObject(tinyxml2::XMLElement* element)
{
    // Parse properties
	m_name = element->Attribute("name");
	m_typeString = element->Attribute("type");

    auto properties = element->FirstChildElement("properties");
    if(properties != 0)
    {
        parseProperties(properties);
    }

    // Parse actual object
	m_rectangle.x = element->FloatAttribute("x");
	m_rectangle.y = element->FloatAttribute("y");

	// There are only 3 possibilities here but use else if for future compability
	if(element->UnsignedAttribute("width") != 0)
	{
		// Rectangle
		m_type = RECTANGLE;
		m_rectangle.width = element->FloatAttribute("width");
		m_rectangle.height = element->FloatAttribute("height");

		m_points.push_back(umath::vector2(m_rectangle.x, m_rectangle.y));
		m_points.push_back(umath::vector2(m_rectangle.x, m_rectangle.y));
		m_points.push_back(umath::vector2(m_rectangle.x, m_rectangle.y));
		m_points.push_back(umath::vector2(m_rectangle.x, m_rectangle.y));
	}
	else if(element->FirstChildElement("polygon") != 0)
	{
		// Polygon
		m_type = POLYGON;
		std::string points = element->FirstChildElement("polygon")->Attribute("points");
		parsePoints(points);
	}
	else if(element->FirstChildElement("polyline") != 0)
	{
		// Line
		m_type = LINE;
		std::string points = element->FirstChildElement("polyline")->Attribute("points");
		parsePoints(points);
	}
}

void Object::parseProperties(tinyxml2::XMLElement* element)
{
    auto p = element->FirstChildElement("property");
	while(p != 0)
	{
		std::pair<std::string, std::string> tmp;
		tmp.first = p->Attribute("name");
		tmp.second = p->Attribute("value");

		m_properties.insert(tmp);

		p = p->NextSiblingElement("property");
	}
}

void Object::parsePoints(const std::string& points)
{
	std::istringstream pointStream(points);
	std::string point;

	while(std::getline(pointStream, point, ' '))
	{
		std::istringstream componentStream(point);
		std::string x;
		std::string y;
		std::getline(componentStream, x, ',');
		std::getline(componentStream, y);
		// Looks good, right?
		m_points.push_back(umath::vector2(
			static_cast<float>(atoi(x.c_str())),
			static_cast<float>(atoi(y.c_str()))
			));
	}

	// Calculate AABB
	float left = 0;
	float right = 0;
	float top = 0;
	float bottom = 0;
	for(auto it = m_points.begin(); it != m_points.end(); ++it)
	{
		auto point = (*it);
		if(point.x < left)
			left = point.x;
		else if(point.x > right)
			right = point.x;

		if(point.y < bottom)
			bottom = point.y;
		else if(point.y > top)
			top = point.y;
	}

	m_rectangle.x += left;
	m_rectangle.y += bottom;
	m_rectangle.width = right - left;
	m_rectangle.height = top - bottom;
}
