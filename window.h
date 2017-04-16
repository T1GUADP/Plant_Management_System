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
#include  <qscrollbar.h>
#include <qlcdnumber.h>
#include <qspinbox.h>

// #include "adcreader.h"

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
    void modetoggle();

// internal variables for the window class
private:



    QSpinBox     *TargetWaterDisplay;
    QSpinBox     *TargetTemperatureDisplay;
    QSpinBox     *TargetLightDisplay;
    QLCDNumber   *CurrentWaterDisplay;
    QLCDNumber   *CurrentTemperatureDisplay;
    QLCDNumber   *CurrentLightDisplay;
    QPushButton  *ManualWaterTrigger;
    QPushButton  *ManualTemperatureTrigger;
    QPushButton  *ManualLightTrigger;
    QPushButton  *ModifyButton;
    QPushButton  *NewEntryButton;
    QPushButton  *DeleteEntryButton;
    QPushButton  *ApplyButton;
    QPushButton  *Placeholder;
    QComboBox    *PresetComboBox;
    QPushButton  *ExitButton;
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
    QwtPlotCurve *Lightcurve;

    // layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
    QVBoxLayout  *vLayout;  // vertical layout
    QGridLayout  *gLayout;  // horizontal layout
    QGridLayout  *gLayout1;  // horizontal layout
    QGridLayout  *gLayout2;  // horizontal layout
    QHBoxLayout  *hLayout1;  // horizontal layout
    QHBoxLayout  *hLayout;  // horizontal layout
    QVBoxLayout  *VLayout1;  // horizontal layout

    static const int plotDataSize = 100;

    // data arrays for the plot
    double xData[plotDataSize];
    double yData[plotDataSize];
    bool currentmode;
    double gain;
    int count;

//	ADCreader *adcreader;
};

#endif // WINDOW_H
