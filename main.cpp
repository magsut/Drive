#include <gamebase/Gamebase.h>

using namespace gamebase;
using namespace std;

class MyApp : public App
{
    void load()
    {
		//CarPos.x = 180;
		//CarPos.y = 85;
		
		whe1.setPos(-400, 0);
		whe2.setPos(-150, 0);

    }

    void process(Input input)
    {
        using namespace gamebase::InputKey;
		if (input.pressed(D))
		{
			w1 -= 4 * timeDelta();
			w2 -= 4 * timeDelta();
		}
		
		if (input.pressed(A))
		{
			w1 += 4 * timeDelta();
			w2 += 4 * timeDelta();
		}
		
    }

    void move()
    {

		
		auto delta = whe2.pos() - whe1.pos();

		w1 -= 0.5*w1 * timeDelta();
		w2 -= 0.5*w2 * timeDelta();
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

		
	bool isTouch(Vec2 a,Vec2 b, Vec2 c, float r, Vec2 &g)
	{
		auto ab = b - a;
		auto ac = c - a;
		auto bc = c - b;
		auto p = dot(ab,ac) / ab.length();
		if (p < 0)
		{
			if (ac.length() <= r)
			{
				g = a;
				return true;
			}
			return false;
		}
		if ( p > ab.length())
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
		if  (hc.length() <= r)
		{
			g = h;
			return true;
		}
		return false;

	}
		

	Vec2 g;

		float w1;
		float w2;

    Vec2 GEOM[6] = {
        Vec2(0, 154),
        Vec2(165, 154),
        Vec2(165, 86),
        Vec2(333, 86),
        Vec2(333, 154),
        Vec2(512, 154)
    };

    //LayerFromDesign(void,car);
    LayerFromDesign(void, wheel1);
    LayerFromDesign(void, wheel2);
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
