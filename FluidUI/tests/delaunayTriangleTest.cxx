// generated by Fast Light User Interface Designer (fluid) version 1.0302

#include "delaunayTriangleTest.h"
#include "DelaunayTestView.h"
#include "TestModel.h"

CrystalMesh::UI::DelaunayTestView *dtView=(CrystalMesh::UI::DelaunayTestView *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(815, 670, "MainWindow");
    w = o;
    { dtView = new CrystalMesh::UI::DelaunayTestView(278, 100, 446, 400, "glDisplay");
      dtView->box(FL_DOWN_BOX);
      dtView->color(FL_BACKGROUND_COLOR);
      dtView->selection_color(FL_BACKGROUND_COLOR);
      dtView->labeltype(FL_NORMAL_LABEL);
      dtView->labelfont(0);
      dtView->labelsize(14);
      dtView->labelcolor(FL_FOREGROUND_COLOR);
      dtView->align(Fl_Align(FL_ALIGN_CENTER));
      dtView->when(FL_WHEN_RELEASE);
    } // CrystalMesh::UI::DelaunayTestView* dtView
    { Fl_Roller* o = new Fl_Roller(278, 513, 446, 24);
      o->type(1);
      o->maximum(361);
      o->step(1);
      o->callback((Fl_Callback*)vRotate);
    } // Fl_Roller* o
    { Fl_Slider* o = new Fl_Slider(410, 546, 217, 24, "slider:");
      o->type(1);
      o->minimum(-1);
      o->step(0.1);
      o->callback((Fl_Callback*)xShift);
    } // Fl_Slider* o
    { Fl_Roller* o = new Fl_Roller(235, 99, 24, 400);
      o->minimum(-1);
      o->maximum(361);
      o->step(1);
      o->callback((Fl_Callback*)hRotate);
    } // Fl_Roller* o
    { Fl_Group* o = new Fl_Group(40, 190, 185, 100);
      o->box(FL_DOWN_BOX);
      { Fl_Button* o = new Fl_Button(95, 200, 70, 20, "FNext");
        o->callback((Fl_Callback*)buttonFnext);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(145, 230, 70, 20, "EPrev");
        o->callback((Fl_Callback*)buttonEPrev);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(50, 230, 70, 20, "ENext");
        o->callback((Fl_Callback*)buttonEnext);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(95, 260, 70, 20, "FPrev");
        o->callback((Fl_Callback*)buttonFPrev);
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    o->end();
  } // Fl_Double_Window* o
  CrystalMesh::UI::triangleTest_launch();

  w->show(argc, argv);
  return Fl::run();  
  CrystalMesh::UI::triangleTest_tearDown();
}

/**
   //horizontal rotation
*/
void hRotate(Fl_Roller* widget,void*) {
  double angle = widget->value();
  dtView->rotateViewH(angle);
  if (angle > 360){
  	widget->value(0.0);		
  }
  if (angle < 0){
  	widget->value(360.0);	
  }
}

/**
   //horizontal rotation
*/
void vRotate(Fl_Roller * widget, void*) {
  double angle = widget->value();
  dtView->rotateViewV(angle);
}

/**
   shift in x dir
*/
void xShift(Fl_Roller* widget,void*) {
  //shift in x dir
}

void buttonFnext(Fl_Button* widget, void*) {
  CrystalMesh::UI::GLTriangle selected = CrystalMesh::UI::selectedTrigSetNext();
  dtView->setSelectedTrigTo(selected);
}

/**
   //Enext button
*/
void buttonEnext(Fl_Button* widget, void*) {
  CrystalMesh::UI::GLEdge selected = CrystalMesh::UI::selectedEdgeSetNext();
  dtView->setSelectedEdgeTo(selected);
}

/**
   //EPrev button
*/
void buttonEPrev(Fl_Button* widget, void*) {
  CrystalMesh::UI::GLEdge selected = CrystalMesh::UI::selectedEdgeSetPrev();
  dtView->setSelectedEdgeTo(selected);
}

/**
   //FPrev Button
*/
void buttonFPrev(Fl_Button* widget, void*) {
  CrystalMesh::UI::GLTriangle selected = CrystalMesh::UI::selectedTrigSetPrev();
  dtView->setSelectedTrigTo(selected);
}
