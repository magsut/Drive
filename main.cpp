#include <gamebase/Gamebase.h>

using namespace gamebase;
using namespace std;

class MyApp : public App
{
	void load()
	{
		whe1.setPos(-400, 0);
		whe2.setPos(-150, 0);
		blocks.load("map0.json");

	}

	void process(Input input)
	{
		using namespace gamebase::InputKey;
		if (input.pressed(D))
		{
			w1 -= 27 * timeDelta();
			w2 -= 27 * timeDelta();
		}

		if (input.pressed(A))
		{
			w1 += 19 * timeDelta();
			w2 += 19 * timeDelta();
		}

	}

	void move()
	{


		auto delta = whe2.pos() - whe1.pos();

		w1 -= 0.99*w1 * timeDelta();
		w2 -= 0.99*w2 * timeDelta();
		whe1.rotate(w1 * timeDelta());
		whe2.rotate(w2 * timeDelta());

		delta.normalize();
		Vec2 v = delta * whe1.width() / 2 * -w1;

		whe1.move(v * timeDelta());
		whe2.move(v * timeDelta());

		Vec2 offset(180, 85);
		offset.rotate(delta.angle());
		Car.setAngle(delta.angle());
		Car.setPos(whe1.pos() + offset);
	}


	bool isTouch(Vec2 a, Vec2 b, Vec2 c, float r, Vec2 &g)
	{
		auto ab = b - a;
		auto ac = c - a;
		auto bc = c - b;
		auto p = dot(ab, ac) / ab.length();
		if (p < 0)
		{
			if (ac.length() <= r)
			{
				g = a;
				return true;
			}
			return false;
		}
		if (p > ab.length())
		{
			if (bc.length() <= r)
			{
				g = b;
				return true;
			}
			return false;
		}
		auto h = ab.normalize() * p;
		auto hc = c - h;
		if (hc.length() <= r)
		{
			g = h;
			return true;
		}
		return false;

	}


	Vec2 g;

	float w1;
	float w2;

	vector<vector<Vec2>> GEOMS = {
		{ // 0
			Vec2(0, 102),
			Vec2(512,102)
		},
		{ // 1
			Vec2(0, 102),
			Vec2(47, 102),
			Vec2(62, 114),
			Vec2(101, 128),
			Vec2(129, 138),
			Vec2(145, 138),
			Vec2(163, 136),
			Vec2(193, 136),
			Vec2(240, 102),
			Vec2(324, 102),
			Vec2(353, 112),
			Vec2(380, 123),
			Vec2(395, 137),
			Vec2(404, 151),
			Vec2(406, 160),
			Vec2(426, 154),
			Vec2(453, 132),
			Vec2(468, 125),
			Vec2(486, 102),
			Vec2(512, 102)
		},
		{ //2
			Vec2(0, 102),
			Vec2(111,102),
			Vec2(512,257)
		},
		{ //3
			Vec2(0, 275),
			Vec2(401,102),
			Vec2(512,102)
		}
	};

	LayerFromDesign(void, wheel1);
	LayerFromDesign(void, wheel2);
	LayerFromDesign(int, blocks);
	FromDesign(GameObj, whe1);
	FromDesign(GameObj, whe2);
	FromDesign(GameObj, Car);
};

int main(int argc, char** argv)
{
	MyApp app;
	app.setConfig("DriveConfig.json");
	app.setDesign("New.json");
	if (!app.init(&argc, argv))
		return 1;
	app.run();
	return 0;
}
