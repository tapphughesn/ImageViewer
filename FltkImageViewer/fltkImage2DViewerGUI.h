// generated by Fast Light User Interface Designer (fluid) version 1.0009

#ifndef fltkImage2DViewerGUI_h
#define fltkImage2DViewerGUI_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <fltkImage2DViewerWindow.h>
#include <FL/Fl_Value_Slider.H>

class fltkImage2DViewerGUI {
public:
  fltkImage2DViewerGUI();
  Fl_Window *externalWindow;
  fltk::Image2DViewerWindow *imageViewer;
  Fl_Window *intensityWindow;
private:
  inline void cb_Min_i(Fl_Value_Slider*, void*);
  static void cb_Min(Fl_Value_Slider*, void*);
  inline void cb_Max_i(Fl_Value_Slider*, void*);
  static void cb_Max(Fl_Value_Slider*, void*);
public:
  virtual ~fltkImage2DViewerGUI();
  void SetLabel(const char *label);
  void Show(void);
  void Hide(void);
  void Redraw(void);
  virtual void SetMin(double val);
  virtual void SetMax(double val);
  virtual void Update(void);
};
#endif
