#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 这个class为游戏的游戏开头画面物件
	/////////////////////////////////////////////////////////////////////////////
	CGameStateInit::CGameStateInit(CGame* g) : CGameState(g)
	{
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(5193);
	}

	void CGameStateInit::OnInit()
	{
		CDDraw::BltBackColor(DEFAULT_BG_COLOR);		// 将 Back Plain 涂上预设的颜色
		title_bmp.LoadBitmap(IDB_TITLE);
		block_floor_1_ground_bmp.LoadBitmap(IDB_BLOCK_FLOOR_1_GROUND, RGB(0, 0, 255));
		block_floor_2_ground_bmp.LoadBitmap(IDB_BLOCK_FLOOR_2_GROUND, RGB(0, 0, 255));
		player_bmp.LoadBitmap(IDB_PLAYER_1, RGB(0, 0, 255));
		grass_left_bmp.LoadBitmap(IDB_GRASS_LEFT, RGB(0, 0, 255));
		grass_right_bmp.LoadBitmap(IDB_GRASS_RIGHT, RGB(0, 0, 255));
		bush_top_bmp.LoadBitmap(IDB_BUSH_TOP, RGB(0, 0, 255));
		bush_center_1_bmp.LoadBitmap(IDB_BUSH_CENTER_1, RGB(0, 0, 255));
		bush_center_2_bmp.LoadBitmap(IDB_BUSH_CENTER_2, RGB(0, 0, 255));
		bush_left_bmp.LoadBitmap(IDB_BUSH_LEFT, RGB(0, 0, 255));
		bush_right_bmp.LoadBitmap(IDB_BUSH_RIGHT, RGB(0, 0, 255));
	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_ENTER = 13;

		if (nChar == KEY_ENTER)
			GotoGameState(GAME_STATE_OVER);						// 切换至GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo 关闭游戏的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 关闭游戏
	}

	void CGameStateInit::OnShow()
	{
		//
		// 贴上title
		//
		title_bmp.SetTopLeft((SIZE_X - title_bmp.Width()) / 2, SIZE_Y / 7);
		title_bmp.ShowBitmap(false);
		//
		// 贴上floor
		//
		for (int i = 0; i < 20; i++)
		{
			block_floor_1_ground_bmp.SetTopLeft(BLOCK_WIDTH_HEIGHT * i, BLOCK_WIDTH_HEIGHT * 13);
			block_floor_1_ground_bmp.ShowBitmap(false);
			block_floor_2_ground_bmp.SetTopLeft(BLOCK_WIDTH_HEIGHT * i, BLOCK_WIDTH_HEIGHT * 14);
			block_floor_2_ground_bmp.ShowBitmap(false);
		}
		//
		// 贴上player
		//
		player_bmp.SetTopLeft(2 * BLOCK_WIDTH_HEIGHT + 6, SIZE_Y - 2 * BLOCK_WIDTH_HEIGHT - player_bmp.Height());
		player_bmp.ShowBitmap(false);
		////
		//// 贴上grass
		////
		grass_left_bmp.SetTopLeft(6 * BLOCK_WIDTH_HEIGHT + 5, SIZE_Y - 3 * BLOCK_WIDTH_HEIGHT);
		grass_left_bmp.ShowBitmap(false);
		grass_right_bmp.SetTopLeft(7 * BLOCK_WIDTH_HEIGHT + 5, SIZE_Y - 3 * BLOCK_WIDTH_HEIGHT);
		grass_right_bmp.ShowBitmap(false);
		////
		//// 贴上bush
		////
		bush_left_bmp.SetTopLeft(12 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y -  3 * BLOCK_WIDTH_HEIGHT);
		bush_left_bmp.ShowBitmap(false);
		bush_left_bmp.SetTopLeft(13 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y -  4 * BLOCK_WIDTH_HEIGHT);
		bush_left_bmp.ShowBitmap(false);
		bush_right_bmp.SetTopLeft(15 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y - 4 * BLOCK_WIDTH_HEIGHT);
		bush_right_bmp.ShowBitmap(false);
		bush_right_bmp.SetTopLeft(16 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y - 3 * BLOCK_WIDTH_HEIGHT);
		bush_right_bmp.ShowBitmap(false);
		bush_center_1_bmp.SetTopLeft(14 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y - 3 * BLOCK_WIDTH_HEIGHT);
		bush_center_1_bmp.ShowBitmap(false);
		bush_center_2_bmp.SetTopLeft(13 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y - 3 * BLOCK_WIDTH_HEIGHT);
		bush_center_2_bmp.ShowBitmap(false);
		bush_center_2_bmp.SetTopLeft(15 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y - 3 * BLOCK_WIDTH_HEIGHT);
		bush_center_2_bmp.ShowBitmap(false);
		bush_center_2_bmp.SetTopLeft(14 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y - 4 * BLOCK_WIDTH_HEIGHT);
		bush_center_2_bmp.ShowBitmap(false);
		bush_top_bmp.SetTopLeft(14 * BLOCK_WIDTH_HEIGHT + 15, SIZE_Y - 5 * BLOCK_WIDTH_HEIGHT);
		bush_top_bmp.ShowBitmap(false);
		//
		// Demo荧幕字型的使用，不过开发时请尽量避免直接使用字型，改用CMovingBitmap比较好
		//
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Yu Gothic UI");	// 产生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 选用 font f
		pDC->SetBkColor(RGB(160, 180, 250));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->TextOut(230, 240, "Press ENTER Key");
		/*pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");*/

		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");

		/*pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");*/
		pDC->SelectObject(fp);						// 放掉 font f (千万不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 这个class为游戏的结束状态(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g) : CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;

		if (counter < 0)
			GotoGameState(GAME_STATE_RUN);
		//TRACE("GameStateRun OnMove\n");
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 60 * 2; // 2 seconds
		lives--;
	}

	void CGameStateOver::OnInit()
	{
		player_bmp.LoadBitmap(IDB_PLAYER_1, RGB(0, 0, 255));
	}

	void CGameStateOver::OnShow()
	{
		CDDraw::BltBackColor(RGB(0, 0, 0));
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Yu Gothic UI");	// 产生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 选用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		char str[80];								// Demo 数字对字串的转换
		sprintf(str, "x %d", lives);
		pDC->TextOut(310, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千万不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		player_bmp.SetTopLeft(280, 200); // 贴上player
		player_bmp.ShowBitmap(false);
		//TRACE("GameStateOver OnShow\n");
	}

	/////////////////////////////////////////////////////////////////////////////
	// 这个class为游戏的游戏执行物件，主要的游戏程式都在这里
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
	{
	}

	CGameStateRun::~CGameStateRun()
	{
		delete map;
	}

	void CGameStateRun::OnBeginState()
	{
		map->getPlayer()->setIsPlayerDeath(false);
		map->loadLVL();
		CAudio::Instance()->Play(AUDIO_FIELD, true);
	}

	void CGameStateRun::OnMove()							// 移动游戏元素
	{
		if (isLeftPressed) 
		{
			if (!map->getPlayer()->getMove() && firstDir == false && !map->getPlayer()->getChangeMoveDirection()) 
			{
				map->getPlayer()->startMove();
				map->getPlayer()->setMoveDirection(false);
			}
			else if (!isRightPressed && map->getPlayer()->getMoveSpeed() > 0 && firstDir != map->getPlayer()->getMoveDirection()) 
				map->getPlayer()->setChangeMoveDirection();
		}

		if (isRightPressed)  
		{
			if (!map->getPlayer()->getMove() && firstDir == true && !map->getPlayer()->getChangeMoveDirection()) 
			{
				map->getPlayer()->startMove();
				map->getPlayer()->setMoveDirection(true);
			}
			else if (!isLeftPressed && map->getPlayer()->getMoveSpeed() > 0 && firstDir != map->getPlayer()->getMoveDirection())
				map->getPlayer()->setChangeMoveDirection();
		}

		if (map->getPlayer()->getMove() && !isLeftPressed && !isRightPressed)
			map->getPlayer()->resetMove();

		map->Update();
		map->UpdateMinionsCollisions();

		if (map->getPlayer()->IsPlayerDeath())
		{
			isLeftPressed = false;
			isRightPressed = false;
			map->setXPos(0);
			map->setYPos(0);
			map->getPlayer()->SetX(6);
			map->getPlayer()->SetY(SIZE_Y - 2 * BLOCK_WIDTH_HEIGHT - 37);
			map->setIsWin(false);
			CAudio::Instance()->Stop(AUDIO_FIELD);
			GotoGameState(GAME_STATE_OVER);
			//TRACE("GotoGameState(GAME_STATE_OVER);\n");
		}
	}

	void CGameStateRun::OnInit()  								// 游戏的初值及图形设定
	{
		CDDraw::BltBackColor(DEFAULT_BG_COLOR);		// 将 Back Plain 涂上预设的颜色
		/*map.setSpawnPoint();*/
		map = new CGameMap();
		map->LoadBitmap();
		//
		// 此OnInit动作会接到CGameStaterOver::OnInit()，所以进度还没到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭头
		const char KEY_UP = 0x26; // keyboard上箭头
		const char KEY_RIGHT = 0x27; // keyboard右箭头
		const char KEY_DOWN = 0x28; // keyboard下箭头

		if (nChar == KEY_RIGHT)
		{
			isRightPressed = true;

			if (!isLeftPressed)
				firstDir = true;
		}


		if (nChar == KEY_LEFT)
		{
			isLeftPressed = true;

			if (!isRightPressed)
				firstDir = false;
		}

		if (nChar == KEY_UP)
		{
			if (!map->getPlayer()->IsUpPressed()) 
			{
				map->getPlayer()->jump();
				map->getPlayer()->setIsUpPressed(true);
			}
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭头
		const char KEY_UP = 0x26; // keyboard上箭头
		const char KEY_RIGHT = 0x27; // keyboard右箭头
		const char KEY_DOWN = 0x28; // keyboard下箭头

		if (nChar == KEY_RIGHT)
		{
			if (firstDir)
				firstDir = false;

			isRightPressed = false;
		}


		if (nChar == KEY_LEFT)
		{
			if (!firstDir)
				firstDir = true;

			isLeftPressed = false;
		}

		if (nChar == KEY_UP)
		{
			map->getPlayer()->setIsUpPressed(false);
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 处理滑鼠的动作
	{

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 处理滑鼠的动作
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 处理滑鼠的动作
	{
		// 没事。如果需要处理滑鼠移动的话，写code在这里
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 处理滑鼠的动作
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 处理滑鼠的动作
	{

	}

	void CGameStateRun::OnShow()
	{
		if (map->getPlayer()->IsPlayerDeath())
		{
			CDDraw::BltBackColor(RGB(0, 0, 0));
		}
		else
			map->Draw();
	}
}