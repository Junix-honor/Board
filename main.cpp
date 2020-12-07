#include"main.h"
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//设置显示窗口的背景颜色
	glClear(GL_COLOR_BUFFER_BIT);//显示窗口的背景颜色

	//使用正投影将世界坐标系二维矩形区域的内容投影到屏幕上
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}
//自适应屏幕窗口大小改变服务函数
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));

	winWidth = newWidth;
	winHeight = newHeight;
}
void move()
{
	static graph* Move_CG;
	static GLint sx, sy;
	if (!InGraph)//判断移动图元是否确定
		for (auto it = CGlist.rbegin(); it != CGlist.rend(); ++it)
		{
			//寻找移动起点所在的第一图元
			if ((*it)->IsInGraph(CG->getPt()[0]))//IsInGraph第二个参数默认为0.3
			{
				//移动图元已经确定
				InGraph = true;
				//用指针记录移动图元
				Move_CG = (*it);
				//图元的初始位置
				sx = CG->getPt()[1].getx();
				sy = CG->getPt()[1].gety();
			}
		}
	else//如果移动图元已经确定
	{
		//图元的移动偏移量
		GLint dx = CG->getPt()[1].getx() - sx;
		GLint dy = CG->getPt()[1].gety() - sy;
		//移动图元
		Move_CG->move(dx, dy);//移动图元方法
		//更新图元的位置
		sx = CG->getPt()[1].getx();
		sy = CG->getPt()[1].gety();
		glutPostRedisplay();//手动触发图元绘制服务函数，立即重绘图元
	}
}
void erase()
{
	//遍历图元链表
	auto it = CGlist.begin();
	while (it != CGlist.end())
	{
		//橡皮擦经过的图元都要被删除
		if ((*it)->IsInGraph(CG->getPt()[CG->size() - 1],1.0))
		{
			it = CGlist.erase(it);//从图元链表中删除图元
			glutPostRedisplay();//手动触发图元绘制服务函数，立即重绘图元
		}
		else it++;
	}
}
void displayFcn(void)
{
	//反走样
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//设置视图
	glViewport(0, 0, winWidth, winHeight);

	//清空画板
	glClear(GL_COLOR_BUFFER_BIT);
	//绘制当前在绘制的图元
	if (CG)
		CG->DrawGraph();
	//图元移动功能
	if (Bmove && CG->size() > 1)
		move();
	//图元删除功能
	if (Berase && CG->size())
		erase();
	//绘制图元链表的图元
	for (auto it = CGlist.begin(); it != CGlist.end(); ++it)
		(*it)->DrawGraph();

	glFlush();
	glutSwapBuffers();
}
void clear()
{
	InGraph = false;
	CGlist.clear();
}
void output()
{
	//打开输出文件
	ofstream outfile("save.txt");
	//输出图元链表中的图元总数
	outfile << CGlist.size() << endl;
	//遍历图元链表中每一个图元
	for (auto i = CGlist.begin(); i != CGlist.end(); ++i)
	{
		//输出图元类型、图元的特征点数目
		outfile << (*i)->getType() << " " << (*i)->size() << " ";
		vector<screenPt> GraphPt;
		GraphPt = (*i)->getPt();
		//输出每一个图元特征点的坐标信息
		for (auto j = GraphPt.begin(); j != GraphPt.end(); ++j)
		{
			outfile << (*j).getx() << " " << (*j).gety() << " ";
		}
		outfile << endl;
	}
}
void input()
{
	GLint GraphNum;
	//打开输入文件
	ifstream infile("save.txt");
	//输入图元总数
	infile >> GraphNum;
	//遍历每一个图元
	for (int i = 1; i <= GraphNum; i++)
	{
		string type;
		GLint PtNum, x, y;
		//输入图元的类型和图元的特征点的数目
		infile >> type >> PtNum;
		static graph* TCG;
		//根据图元的类型新建图元实例
		TCG = (*typeMap.find(type)).second->renew();
		//遍历每一个特征点
		for (int j = 1; j <= PtNum; j++)
		{
			//输入每一个特征点的坐标信息
			infile >> x >> y;
			//把图元的所有特征点添加到图元实例中
			TCG->push_back(screenPt{ x,y });
			TCG->Pt_increase();
		}
		//把图元实例添加到画板的图元链表中，完成图元的读取
		CGlist.push_front(TCG);
	}
	infile.close();
}
void keyboard(GLubyte key, GLint xMouse, GLint yMouse)
{
	//绘制图元功能
	auto iter = creat_new.find(key);//哈希表寻找
	if (iter != creat_new.end())
		CG = (*iter).second->renew();//创建图元实例
	//标记初始化
	Bmove = false;
	Berase = false;
	//其他功能
	switch (key)
	{
	case'e':case'E'://删除图元功能
		Berase = true;//标记删除图元功能开启
		break;
	case'm':case'M'://移动图元功能
		Bmove = true;//标记移动图元功能开启
		break;
	case'i':case'I'://读取图元功能
		input();//图元读取函数
		glutPostRedisplay();//重绘图元
		break;
	case'o':case'O':
		output();//图元保存函数
		break;
	case'0':
		clear();//画板清空函数
		glutPostRedisplay();//重绘图元
		break;
	case 27:
		exit(0);//退出程序
		break;
	default:
		break;
	}
}
void mouseButton(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	//鼠标左键从松开到按下的一瞬间
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		//如果是第一次鼠标左键从松开到按下，代表绘制图元的起点，这个点直接就被确定，不需要调整
		if (CG && CG->Pt_num() == 0)
		{
			CG->push_back(screenPt{ xMouse ,winHeight - yMouse });//插入特征点
			CG->Pt_increase();//PtCtr加1代表确定的特征点增加了一个
		}

	}
	//鼠标左键从按下到松开的一瞬间
	else if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
	{
		if (CG)
		{
			CG->push_back(screenPt{ xMouse ,winHeight - yMouse });//插入特征点
			CG->Pt_increase();//PtCtr加1代表确定的特征点增加了一个
		}
		//如果绘制已经完成
		if (CG && CG->IsEnd())
		{
			//因为Move图元是一个移动轨迹，所以，不需要加到图元链表中
			if (!(Bmove || Berase))
				CGlist.push_front(CG);//把图元加到链表中
			InGraph = false;
			//新建图元实例，为下一次绘制做好准备
			CG = CG->renew();
		}
	}
	glutPostRedisplay();//手动触发图元绘制服务函数，立即重绘图元
}
void mouseMotion(GLint xMouse, GLint yMouse)
{
	if (CG)
		///更新下一个特征点的信息
		CG->push_back(screenPt{ xMouse ,winHeight - yMouse });
	glutPostRedisplay();//手动触发图元绘制服务函数，立即重绘图元
}
int main(int argc, char** argv)
{
	//初始化

	//glut初始化
	glutInit(&argc, argv);
	//设定显示窗口的缓冲和颜色模型等
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_SINGLE | GLUT_RGB);
	//给定显示窗口左上角的初始位置
	glutInitWindowPosition(100, 100);
	//设定显示窗口的初始宽度和高度的像素数
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Bitman");//设置显示窗口
	init();//画板初始化函数


	//绘图服务函数
	glutDisplayFunc(displayFcn);

	//自适应屏幕窗口大小改变服务函数
	glutReshapeFunc(winReshapeFcn);

	//鼠标服务函数
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	//键盘服务函数
	glutKeyboardFunc(keyboard);

	//进入GLUT事件处理循环
	glutMainLoop();
}