#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qpushbutton.h>
#include <QBoxLayout>
#include <qlabel.h>
#include <qcombobox.h>
#include <qslider.h>
#include <qscrollbar.h>
#include <qlcdnumber.h>
#include <qspinbox.h>
#include <qcolor.h>

#include "adcreader.h"

// class definition 'Window'
class Window : public QWidget
{
    // must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
    Q_OBJECT

public:
    Window(); // default constructor - called when a Window is declared without arguments

    ~Window();

    void timerEvent( QTimerEvent * );

public slots:
    void setGain(double gain);
    void setWaterTarget(int TargetWaterLevel);
    void setTemperatureTarget(int TargetWaterLevel);
    void setLightTarget(int TargetWaterLevel);

    void modetoggle();

// internal variables for the window class
private:



    QSpinBox     *TargetWaterDisplay;
    QSpinBox     *TargetTemperatureDisplay;
    QSpinBox     *TargetLightDisplay;

    QPushButton  *ManualWaterTrigger;
    QPushButton  *ManualTemperatureTrigger;
    QPushButton  *ManualLightTrigger;
    QPushButton  *ExitButton;   
    QLabel       *Waterlabel;
    QLabel       *Temperaturelabel;
    QLabel       *Lightlabel;
    QLabel       *CurrentWaterDisplay;
    QLabel       *CurrentTemperatureDisplay;
    QLabel       *CurrentLightDisplay;
    QLabel       *ModeTextLabel1;
    QLabel       *ModeTextLabel2;
    QLabel       *TargetWaterLabel;
    QLabel       *TargetTemperatureLabel;
    QLabel       *TargetLightLabel;
    QLabel       *CurrentWaterLabel;
    QLabel       *CurrentTemperatureLabel;
    QLabel       *CurrentLightLabel;
    QLabel       *WaterSensorConnectionStateLabel;
    QLabel       *TemperatureSensorConnectionStateLabel;
    QLabel       *LightSensorConnectionStateLabel;
    QPushButton  *ModeButton;
    QwtKnob      *knob;
    QwtThermo    *thermo;
    QwtPlot      *plot;
    QwtPlot      *WaterPlot;
    QwtPlot      *TemperaturePlot;
    QwtPlot      *LightPlot;
    QwtPlotCurve *curve;
    QwtPlotCurve *Watercurve;
    QwtPlotCurve *Temperaturecurve;
    QwtPlotCurve *TargetWaterCurve;
    QwtPlotCurve *TargetTemperatureCurve;
    QwtPlotCurve *TargetLightCurve;
    QwtPlotCurve *Lightcurve;

    // layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html

    QGridLayout  *gLayout;  // horizontal layout
    QGridLayout  *gLayout1;  // grid layout
    QGridLayout  *gLayout2;  // grid layout
    QGridLayout  *SecondRowglayout; // Second row horizontal layout
    QHBoxLayout  *hLayout1;  // horizontal layout
    QHBoxLayout  *hLayout;  // horizontal layout
    QVBoxLayout  *vLayout;  // vertical layout
    QVBoxLayout  *VLayout1;  // Vertical layout

    static const int plotDataSize = 200;

    // data arrays for the plot
    double xData[plotDataSize];
    double yData[plotDataSize];
    //
    double xTargetWaterData[plotDataSize];
    double yTargetWaterData[plotDataSize];
    double xTargetTemperatureData[plotDataSize];
    double yTargetTemperatureData[plotDataSize];
    double xTargetLightData[plotDataSize];
    double yTargetLightData[plotDataSize];
    //
    double gain;
    int TargetWaterLevel;
    int TargetTemperatureLevel;
    int TargetLightLevel;
    int count;
    //
    bool currentmode;
    //

//	ADCreader *adcreader;
};

#endif // WINDOW_H
