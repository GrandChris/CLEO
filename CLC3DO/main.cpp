//////////////////////////////////////////////////////////////////////////////
// File: main.cpp
// Date: 15.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: Entrypoint
///////////////////////////////////////////////////////////////////////////////

#include <ParticleRenderer.h>
#include <TwoPointMovingRenderObject.h>

#include <Coroutine.h>
#include "Circle.h"
#include "HalfCircle.h"
#include "MultiObject.h"

#include <iostream>
#include <numeric>
#include <tuple>
#include <random>

using namespace std;

struct Vertex
{
	glm::vec2 pos;
	glm::vec3 color;
};


template<typename T>
Generator<std::tuple<float, float>> fill(T const& circle)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distributionX(circle.minX(), circle.maxX());
	std::uniform_real_distribution<float> distributionY(circle.minY(), circle.maxY());

	while (true)
	{
		auto const x = distributionX(generator);
		auto const y = distributionY(generator);

		if (circle.isInside({ x, y }))
		{
			co_yield(std::tuple<float, float>(x, y));
		}
	}
}



Generator<Vertex> generateVertices(Generator<std::tuple<float, float>>& src)
{
	float const r = 0.2f;
	float const g = 0.5f;
	float const b = 0.5f;
	for (auto const val : src)
	{
		Vertex vertex;
		vertex.pos.x = std::get<0>(val);
		vertex.pos.y = std::get<1>(val);
		vertex.color.r = r;
		vertex.color.g = g;
		vertex.color.b = b;

		co_yield vertex;
	}
}


Generator<Vertex> colorGradient(Generator<Vertex>& src,
	Vertex const& start, Vertex const& stop)
{
	auto const direction = (stop.pos - start.pos);
	auto const deltaColor = (stop.color - start.color) /  glm::length(direction);

	for (auto val : src)
	{
		if(glm::dot(val.pos - start.pos, direction) < 0 ||
			glm::dot(val.pos - stop.pos, direction) > 0)
		{	// not inside 
			co_yield val;
		}
		else
		{	
			auto const dist = glm::dot((val.pos - start.pos), glm::normalize(direction));
			auto const color = start.color + deltaColor * dist;

			val.color = color;

			co_yield val;
		}
	}
}



void drawStuff()
{
	// create Object

	float const r = 1.0;

	MultiObject obj;
	auto circle = std::make_unique<Circle>(r);
	circle->setPos({ -r, 0 });

	auto halfCircle1 = std::make_unique<HalfCircle>(r);
	halfCircle1->setPos({ 0, 0 });

	auto halfCircle2 = std::make_unique<HalfCircle>(r);
	halfCircle2->setPos({ r, 0 });

	obj.add(std::move(circle));
	obj.add(std::move(halfCircle1));
	obj.add(std::move(halfCircle2));

	// fill with points

	auto filledCirlce = fill(obj);

#ifdef _DEBUG 
	auto points = take(filledCirlce, 15'000);
#else
	auto points = take(filledCirlce, 15'000'000);
#endif

	auto vertices = generateVertices(points);

	// create color gradient	

	Vertex const color1 = { {obj.minX(), 0},
		{54.0f/256.0f, 158.0f/256.0f, 94.0f/256.0f} };
	Vertex const color2 = { {obj.minX() + (obj.maxX() - obj.minX())/2.0, 0},
		{47.0f / 256.0f, 93.0f / 256.0f, 176.0f / 256.0f} };
	Vertex const color3 = { {obj.maxX(), 0},
		{155.0f / 256.0f, 36.0f / 256.0f, 67.0f / 256.0f} };

	auto colorVertices = colorGradient(vertices, color1, color2);
	auto colorVertices2 = colorGradient(colorVertices, color2, color3);

	// create vertices

	std::default_random_engine generator;
	std::normal_distribution<float> distribution(1.5f, 0.5f);
	std::normal_distribution<float> distribution2(0.0f, 0.5f);
	std::vector<TwoPointMovingRenderObject::Vertex> vertexVec;
	for (auto const& elem : colorVertices2)
	{
		glm::vec3 vertexA = { elem.pos.x, elem.pos.y, 0.0f };
		glm::vec3 vertexB = { elem.pos.x + distribution2(generator),
			elem.pos.y + distribution2(generator),
			distribution(generator) };

		vertexVec.push_back({ vertexA, vertexB, elem.color });
	}

	//draw
	auto const app = ParticleRenderer::createVulkan();


	auto rendObj = TwoPointMovingRenderObject::createVulkan();
	rendObj->setVertices(vertexVec);
	rendObj->setPosition({ -4.0f, 0.0f, 0.0f });

	//app->setWindowSize(2560, 1440);
	//app->setVSync(true);

	app->add(std::move(rendObj));
	app->run();
}





int main() 
{
	drawStuff();

	return 0;
}


int WinMain()
{
	main();

	return 0;
}


