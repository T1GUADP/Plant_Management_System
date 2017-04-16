#include "window.h"

#include <cmath>  // for sine stuff
#include <math.h>  //
#include <wiringPi.h>
#include <unistd.h>
#include "adcreader.h"
#include <iostream>

using namespace std;

Window::Window(Buffer *buffer) : TargetWaterLevel(0), TargetTemperatureLevel(0), TargetLightLevel(0), count(0), currentmode(true)
{

    this->buffer = buffer;
    this->adcReader0 = new ADCreader(buffer, 0);
    this->adcReader0->start();


    //first row Interactables
    ModeButton = new QPushButton;   //Creates toggle Auto/Manual mode button
    ModeButton->setText("Toggle Plot");  //Sets text for ModeButton
    ModeTextLabel1 = new QLabel; // Creates description label
    ModeTextLabel1->setText("Current Plot: "); //Sets text for ModeTextLabel1
    ModeTextLabel2 = new QLabel; //Creates label to show the current mode
    ModeTextLabel2->setText("Light plot (Channel:0)"); //Sets initial text for ModeTextLabel2
    ExitButton = new QPushButton; //creates exit button
    ExitButton->setText("Exit Program"); //sets exit button text
    //firstrow layout (Creates new gridlayout and adds the first row Interactables)
    gLayout = new QGridLayout;
    gLayout->addWidget(ModeButton,0,0,Qt::AlignLeft);
    gLayout->addWidget(ModeTextLabel1,0,1,Qt::AlignRight);
    gLayout->addWidget(ModeTextLabel2,0,2,Qt::AlignLeft);
    gLayout->addWidget(ExitButton,0,4,Qt::AlignRight);
    //firstrow functions
    connect( ExitButton, SIGNAL(pressed()), SLOT(close()) ); //Gives "Exit button" the function to exit upon being pressed.
    connect( ModeButton, SIGNAL(pressed()), SLOT(modetoggle()) ); //Gives "ModeButton" triggers "modetoggle" function
    //modetoggle()
    //Second row Interactables
    MainPlot = new QwtPlot;
    MainCurve = new QwtPlotCurve;
    MainTargetCurve = new QwtPlotCurve;
    Watercurve = new QwtPlotCurve; //Assignes curve to plot
    TargetWaterCurve = new QwtPlotCurve;
    Temperaturecurve = new QwtPlotCurve;
    TargetTemperatureCurve = new QwtPlotCurve;
    Lightcurve = new QwtPlotCurve;
    TargetLightCurve = new QwtPlotCurve;
    //second row layout
    hLayout = new QHBoxLayout; //Creates new Horizontal layout
    hLayout->addWidget(MainPlot);
    //Third row Interactables
    CurrentWaterDisplay = new QLabel;
    CurrentTemperatureDisplay = new QLabel;
    CurrentLightDisplay = new QLabel;
    TargetWaterDisplay = new QSpinBox;
    TargetTemperatureDisplay = new QSpinBox;
    TargetLightDisplay = new QSpinBox;
    TargetWaterLabel = new QLabel;
    TargetTemperatureLabel = new QLabel;
    TargetLightLabel = new QLabel;
    TargetWaterLabel->setText("Target:");
    TargetTemperatureLabel->setText("Target:");
    TargetLightLabel->setText("Target:");
    CurrentWaterLabel = new QLabel;
    CurrentTemperatureLabel = new QLabel;
    CurrentLightLabel = new QLabel;
    CurrentWaterLabel->setText("Current:");
    CurrentTemperatureLabel->setText("Current:");
    CurrentLightLabel->setText("Current:");
    //Fourth row Layout
    gLayout1 = new QGridLayout;
    gLayout1->addWidget(TargetWaterLabel,0,0,Qt::AlignCenter);
    gLayout1->addWidget(CurrentWaterLabel,0,2,Qt::AlignCenter);
    gLayout1->addWidget(TargetTemperatureLabel,0,4,Qt::AlignCenter);
    gLayout1->addWidget(CurrentTemperatureLabel,0,6,Qt::AlignCenter);
    gLayout1->addWidget(TargetLightLabel,0,8,Qt::AlignCenter);
    gLayout1->addWidget(CurrentLightLabel,0,10,Qt::AlignCenter);
    gLayout1->addWidget(TargetWaterDisplay,0,1,Qt::AlignCenter);
    gLayout1->addWidget(CurrentWaterDisplay,0,3,Qt::AlignCenter);
    gLayout1->addWidget(TargetTemperatureDisplay,0,5,Qt::AlignCenter);
    gLayout1->addWidget(CurrentTemperatureDisplay,0,7,Qt::AlignCenter);
    gLayout1->addWidget(TargetLightDisplay,0,9,Qt::AlignCenter);
    gLayout1->addWidget(CurrentLightDisplay,0,11,Qt::AlignCenter);
    //Fourth row functionality
    connect( TargetWaterDisplay, SIGNAL(valueChanged(int)), SLOT(setWaterTarget(int)) );
    connect( TargetTemperatureDisplay, SIGNAL(valueChanged(int)), SLOT(setTemperatureTarget(int)) );
    connect( TargetLightDisplay, SIGNAL(valueChanged(int)), SLOT(setLightTarget(int)) );
    //Fifth row Interactables
    WaterSensorConnectionStateLabel = new QLabel;
    WaterSensorConnectionStateLabel->setText("Connected");
    TemperatureSensorConnectionStateLabel = new QLabel;
    TemperatureSensorConnectionStateLabel->setText("Connected");
    LightSensorConnectionStateLabel = new QLabel;
    LightSensorConnectionStateLabel->setText("Connected");
    ManualWaterTrigger = new QPushButton;
    ManualWaterTrigger->setText("Release Water");
    ManualTemperatureTrigger = new QPushButton;
    ManualTemperatureTrigger->setText("Increase Temperature");
    ManualLightTrigger = new QPushButton;
    ManualLightTrigger->setText("Toggle Light");
    //Fifth row Layout
    gLayout2 = new QGridLayout;
    gLayout2->addWidget(WaterSensorConnectionStateLabel,0,0,Qt::AlignCenter);
    gLayout2->addWidget(ManualWaterTrigger,0,1,Qt::AlignCenter);
    gLayout2->addWidget(TemperatureSensorConnectionStateLabel,0,2,Qt::AlignCenter);
    gLayout2->addWidget(ManualTemperatureTrigger,0,3,Qt::AlignCenter);
    gLayout2->addWidget(LightSensorConnectionStateLabel,0,4,Qt::AlignCenter);
    gLayout2->addWidget(ManualLightTrigger,0,5,Qt::AlignCenter);

        // set up the initial plot data
        for( int index=0; index<plotDataSize; ++index )
        {
            xCurrentWaterData[index] = index;
            yCurrentWaterData[index] = 0;
            xCurrentTemperatureData[index]= index;
            yCurrentTemperatureData[index] = 0;
            xCurrentLightData[index]= index;
            yCurrentLightData[index] = 0;
            //yData[index] = gain * sin( M_PI * index/50 );
        }
        // set up the initial plot target data
        for( int index=0; index<plotDataSize; ++index )
        {
            xTargetWaterData[index] = index;
            yTargetWaterData[index] = TargetWaterLevel ;
            xTargetTemperatureData[index] = index;
            yTargetTemperatureData[index] = TargetWaterLevel ;
            xTargetLightData[index] = index;
            yTargetLightData[index] = TargetWaterLevel ;
        }


        //Set samples for curves and attach to plots
        MainCurve->attach(MainPlot);
        MainTargetCurve->attach(MainPlot);
        MainTargetCurve->setPen( QColor( Qt::red ) );


        MainPlot->replot();
        MainPlot->show();
        vLayout = new QVBoxLayout;


        hLayout1 = new QHBoxLayout;
        hLayout1->addLayout(vLayout);

        VLayout1 = new QVBoxLayout;
        VLayout1->addLayout(gLayout);
        VLayout1->addLayout(hLayout);
        VLayout1->addLayout(gLayout1);
        VLayout1->addLayout(gLayout2);
        setLayout(VLayout1);


}

Window::~Window() {
}
double lightinputvalue;
double temperatureinputvalue;
double inVal;


void Window::timerEvent( QTimerEvent * )
{

    if (currentmode==true)
    {
        //get average from buffer
        double lightinputvalue = this->buffer->calculatesAvg(0)*10;//*(-1)-9285;//-9285; //*(adcReader0->currentValue)*(-1)-9270;
        //prevent negative values
        if (lightinputvalue<0){lightinputvalue=0;}
        //move array by 1
        memmove( yCurrentLightData, yCurrentLightData+1, (plotDataSize-1) * sizeof(double) );
        //add to displayed values
        yCurrentLightData[plotDataSize-1] = lightinputvalue;
        //set plot values to temperature
        MainCurve->setSamples(xCurrentLightData, yCurrentLightData, plotDataSize);
        MainTargetCurve->setSamples(xTargetLightData, yTargetLightData, plotDataSize);
        //set axis label and scale
        MainPlot->setAxisTitle(0,"Light intensity (%)");
        MainPlot->setAxisTitle(2,"Data index");
        MainPlot->setAxisScale(0,0,100,10);
        //replot plot
        MainPlot->replot();
        //update label
        CurrentLightDisplay-> setText(QString::number(round(lightinputvalue*10)/10));
        //turn on heat (not implemented)
        if (lightinputvalue<TargetLightLevel)
        {
           LightSensorConnectionStateLabel->setText("Too Low");
           //digitalWrite (0, HIGH) ; delay (500);
        }
        //turn off heat (not implemented)
        else
        {
           LightSensorConnectionStateLabel->setText("Ok");
           //digitalWrite (0,  LOW) ; delay (500);
        }

    }
    else if (currentmode==false)
    {
        double  temperatureinputvalue= this->buffer->calculatesAvg(1)*(-0.1715)-1595;
        if (temperatureinputvalue<0){temperatureinputvalue=0;}
        memmove( yCurrentTemperatureData, yCurrentTemperatureData+1, (plotDataSize-1) * sizeof(double) );
        yCurrentTemperatureData[plotDataSize-1] = temperatureinputvalue;
        MainCurve->setSamples(xCurrentTemperatureData, yCurrentTemperatureData, plotDataSize);
        MainTargetCurve->setSamples(xTargetTemperatureData, yTargetTemperatureData, plotDataSize);
        MainPlot->setAxisTitle(0,"Temperature (C)");
        MainPlot->setAxisTitle(2,"Data index");
        MainPlot->setAxisScale(0,0,50,5);
        MainPlot->replot();
        CurrentTemperatureDisplay-> setText((QString::number(round(temperatureinputvalue*10)/10))+"C");
        if (temperatureinputvalue<TargetTemperatureLevel)
        {
           TemperatureSensorConnectionStateLabel->setText("Too Low");
           //digitalWrite (0, HIGH) ; delay (500);
        }
        else
        {
           TemperatureSensorConnectionStateLabel->setText("Ok");
           //digitalWrite (0,  LOW) ; delay (500);
        }
    }
    else
    {
        //third channel not implemented
        cout << "Window: channel not implemented"<< endl;
    }
}


//change values shown on the main plot to the water values
void Window::setWaterTarget(int TargetWaterLevel)
{
    this->TargetWaterLevel = TargetWaterLevel;
    for( int index=0; index<plotDataSize; ++index )
    {
        xTargetWaterData[index] = index;
        yTargetWaterData[index] = TargetWaterLevel ;
    }
    MainPlot->replot();
    MainPlot->show();
}
//change values shown on the main plot to the temperature values
void Window::setTemperatureTarget(int TargetTemperatureLevel)
{
    this->TargetTemperatureLevel = TargetTemperatureLevel;
    for( int index=0; index<plotDataSize; ++index )
    {
        xTargetTemperatureData[index] = index;
        yTargetTemperatureData[index] = TargetTemperatureLevel ;
    }
    MainPlot->replot();
    MainPlot->show();
}
//change values shown on the main plot to the Light values
void Window::setLightTarget(int TargetLightLevel)
{
    this->TargetLightLevel = TargetLightLevel;
    for( int index=0; index<plotDataSize; ++index )
    {
        xTargetLightData[index] = index;
        yTargetLightData[index] = TargetLightLevel ;
    }

    MainPlot->replot();
    MainPlot->show();
}
//change between channel 0 and channel 1
void Window::modetoggle()
{

    currentmode = !currentmode;
    if (currentmode == false){
        this->adcReader1 = new ADCreader(buffer, 1);
        //terminate channel/thread 0 and start channel/thread 1
        adcReader0->terminate();
        adcReader1->start();
        ModeTextLabel2->setText("Temperature plot (Channel:1)");
    }
    else if (currentmode == true)
    {
        this->adcReader0 = new ADCreader(buffer, 0);
        //terminate channel/thread 1 and start channel/thread 0
        adcReader1->terminate();
        adcReader0->start();
        ModeTextLabel2->setText("Light plot (Channel:0)");
    }

}

