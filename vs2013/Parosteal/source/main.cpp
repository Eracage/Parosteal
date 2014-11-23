#include <UtH/uthEngine.hpp>

#define NEWSCENEFUNC
#include <Scenes.hpp>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	srand(time(0));

	uthSceneM.registerNewSceneFunc(NewSceneFunc, COUNT);

	uthEngine.Init();

	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);

	while (uthEngine.Running())
	{
		if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Escape))
			uthEngine.Exit();

		uthEngine.Update();

		uthEngine.Draw();
	}

	return 0;
}


int main()
{
	srand(time(0));

	uthSceneM.registerNewSceneFunc(NewSceneFunc,COUNT);

	uthEngine.Init();

	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);

	while(uthEngine.Running())
	{
		if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Escape))
			uthEngine.Exit();

		uthEngine.Update();

		uthEngine.Draw();
	}

	return 0;
	//Hood.MainLoop(/*new StartScene*/);
	//uthSceneM.GoToScene(/*new GameScene*/1);
}