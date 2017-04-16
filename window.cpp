#include "window.h"

#include <cmath>  // for sine stuff
#include <math.h>  //
#include <wiringPi.h>

#include "adcreader.h"
#include <iostream>

using namespace std;

Window::Window(Buffer *buffer) : gain(5), TargetWaterLevel(0), TargetTemperatureLevel(0), TargetLightLevel(0), count(0), currentmode(true)
{

    this->buffer = buffer;

    this->adcReader22 = new ADCreader(buffer, 22); //22 27
    this->adcReader22->start();


    //first row Interactables
    ModeButton = new QPushButton;   //Creates toggle Auto/Manual mode button
    ModeButton->setText("Toggle Mode");  //Sets text for ModeButton
    ModeTextLabel1 = new QLabel; // Creates description label
    ModeTextLabel1->setText("Current Mode: "); //Sets text for ModeTextLabel1
    ModeTextLabel2 = new QLabel; //Creates label to show the current mode
    ModeTextLabel2->setText("Placeholder"); //Sets initial text for ModeTextLabel2
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
    Waterlabel = new QLabel;
    Waterlabel->setText("Water Measurement");
    Temperaturelabel = new QLabel;
    Temperaturelabel->setText("Temperature Measurement");
    Lightlabel = new QLabel;
    Lightlabel->setText("Light Measurement");
    //Second row layout (adds widgets to gridlayout)
    SecondRowglayout = new QGridLayout;
    SecondRowglayout->addWidget(Waterlabel,0,0,Qt::AlignCenter);
    SecondRowglayout->addWidget(Temperaturelabel,0,1,Qt::AlignCenter);
    SecondRowglayout->addWidget(Lightlabel,0,2,Qt::AlignCenter);
    //Third row Interactables
    WaterPlot =new QwtPlot; //Creates new plot
    Watercurve = new QwtPlotCurve; //Assignes curve to plot
    TargetWaterCurve = new QwtPlotCurve;
    TemperaturePlot =new QwtPlot;
    Temperaturecurve = new QwtPlotCurve;
    TargetTemperatureCurve = new QwtPlotCurve;
    LightPlot = new QwtPlot;
    Lightcurve = new QwtPlotCurve;
    TargetLightCurve = new QwtPlotCurve;
    //Third row layout
    hLayout = new QHBoxLayout; //Creates new Horizontal layout
    hLayout->addWidget(WaterPlot); //Assigns widget to horizontal layout
    hLayout->addWidget(TemperaturePlot);
    hLayout->addWidget(LightPlot);
    //Fourth row Interactables
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
    //Fifth row functionality




    knob = new QwtKnob;
        // set up the gain knob
        knob->setValue(gain);

        // use the Qt signals/slots framework to update the gain -
        // every time the knob is moved, the setGain function will be called
        connect( knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );

        // set up the thermometer
        thermo = new QwtThermo;
        thermo->setFillBrush( QBrush(Qt::red) );
        //thermo->setRange(0, 20);
        thermo->show();


        // set up the initial plot data
        for( int index=0; index<plotDataSize; ++index )
        {
            xData[index] = index;
            yData[index] = 0;
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

        curve = new QwtPlotCurve;
        plot = new QwtPlot;
        // make a plot curve from the data and attach it to the plot
        curve->setSamples(xData, yData, plotDataSize);
        curve->attach(plot);
        Watercurve->setSamples(xData, yData, plotDataSize);
        Watercurve->attach(WaterPlot);
        TargetWaterCurve->setSamples(xTargetWaterData, yTargetWaterData, plotDataSize);
        TargetWaterCurve->attach(WaterPlot);
        TargetWaterCurve->setPen( QColor( Qt::red ) );
        Temperaturecurve->setSamples(xData, yData, plotDataSize);
        Temperaturecurve->attach(TemperaturePlot);
        TargetTemperatureCurve->setSamples(xTargetTemperatureData, yTargetTemperatureData, plotDataSize);
        TargetTemperatureCurve->attach(TemperaturePlot);
        TargetTemperatureCurve->setPen( QColor( Qt::red ) );
        Lightcurve->setSamples(xData, yData, plotDataSize);
        Lightcurve->attach(LightPlot);
        TargetLightCurve->setSamples(xTargetLightData, yTargetLightData, plotDataSize);
        TargetLightCurve->attach(LightPlot);
        TargetLightCurve->setPen( QColor( Qt::red ) );
        plot->replot();
        plot->show();
        WaterPlot->replot();
        WaterPlot->show();
        TemperaturePlot->replot();
        TemperaturePlot->show();
        LightPlot->replot();
        LightPlot->show();

        vLayout = new QVBoxLayout;
        vLayout->addWidget(knob);
        vLayout->addWidget(thermo);

        hLayout1 = new QHBoxLayout;
        hLayout1->addLayout(vLayout);
        hLayout1->addWidget(plot);

        VLayout1 = new QVBoxLayout;
        VLayout1->addLayout(gLayout);
        VLayout1->addLayout(SecondRowglayout);
        //VLayout1->addLayout(hLayout1);
        VLayout1->addLayout(hLayout);
        VLayout1->addLayout(gLayout1);
        VLayout1->addLayout(gLayout2);
        setLayout(VLayout1);


    // This is a demo for a thread which can be
    // used to read from the ADC asynchronously.
    // At the moment it doesn't do anything else than
    // running in an endless loop and which prints out "tick"
    // every second.
//	adcreader = new ADCreader();
//	adcreader->start();
}

Window::~Window() {
    // tells the thread to no longer run its endless loop
    //adcreader->quit();
    // wait until the run method has terminated
    //adcreader->wait();
    //delete adcreader;
}




void Window::timerEvent( QTimerEvent * )
{
    double inVal = gain * sin( M_PI * count/50.0 );
    ++count;

    //cout << "Test " << *(adcReader22->currentValue) << endl;

    // get values from buffer
    double waterinputvalue = inVal;
    double temperatureinputvalue = this->buffer->calculatesAvg(22)*(-1)-9250; //*(adcReader22->currentValue)*(-1)-9270;


    double lightinputvalue = inVal;
    // add the new input to the plot
    {
    memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
    yData[plotDataSize-1] = inVal;

    memmove( yCurrentWaterData, yCurrentWaterData+1, (plotDataSize-1) * sizeof(double) );
    yCurrentWaterData[plotDataSize-1] = waterinputvalue;

    memmove( yCurrentTemperatureData, yCurrentTemperatureData+1, (plotDataSize-1) * sizeof(double) );
    yCurrentTemperatureData[plotDataSize-1] = temperatureinputvalue;

    memmove( yCurrentLightData, yCurrentLightData+1, (plotDataSize-1) * sizeof(double) );
    yCurrentLightData[plotDataSize-1] = lightinputvalue;
    }
    //Conditions
    {
    if (inVal<TargetWaterLevel)
    {
       WaterSensorConnectionStateLabel->setText("Too Low");
       //digitalWrite (0, HIGH) ; delay (500);
    }
    else
    {
       WaterSensorConnectionStateLabel->setText("Ok");
       //digitalWrite (0,  LOW) ; delay (500);
    }
    if (inVal<TargetTemperatureLevel)
    {
       TemperatureSensorConnectionStateLabel->setText("Too Low");
       //digitalWrite (0, HIGH) ; delay (500);
    }
    else
    {
       TemperatureSensorConnectionStateLabel->setText("Ok");
       //digitalWrite (0,  LOW) ; delay (500);
    }
    if (inVal<TargetLightLevel)
    {
       LightSensorConnectionStateLabel->setText("Too Low");
       //digitalWrite (0, HIGH) ; delay (500);
    }
    else
    {
       LightSensorConnectionStateLabel->setText("Ok");
       //digitalWrite (0,  LOW) ; delay (500);
    }
    }
    //Set Plotdata
    {
    curve->setSamples(xData, yData, plotDataSize);
    Watercurve->setSamples(xCurrentWaterData, yCurrentWaterData, plotDataSize);
    Temperaturecurve->setSamples(xCurrentTemperatureData, yCurrentTemperatureData, plotDataSize);
    Lightcurve->setSamples(xCurrentLightData, yCurrentLightData, plotDataSize);
    }
    //Plot data
    {
    plot->replot();
    WaterPlot->replot();
    TemperaturePlot->replot();
    LightPlot->replot();
    }
    // set the thermometer value
    thermo->setValue( inVal + 10 );
    //update "Current:" values in the fifth row
    {
    CurrentWaterDisplay-> setText(QString::number(round(inVal*10)/10));
    CurrentTemperatureDisplay-> setText((QString::number(round(inVal*10)/10))+"C");
    CurrentLightDisplay-> setText(QString::number(round(inVal*10)/10));
    }

}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
    // for example purposes just change the amplitude of the generated input
    this->gain = gain;
}


void Window::setWaterTarget(int TargetWaterLevel)
{
    // for example purposes just change the amplitude of the generated input
    this->TargetWaterLevel = TargetWaterLevel;
    for( int index=0; index<plotDataSize; ++index )
    {
        xTargetWaterData[index] = index;
        yTargetWaterData[index] = TargetWaterLevel ;
    }
    TargetWaterCurve->setSamples(xTargetWaterData, yTargetWaterData, plotDataSize);
    WaterPlot->replot();
    WaterPlot->show();
}
void Window::setTemperatureTarget(int TargetTemperatureLevel)
{
    // for example purposes just change the amplitude of the generated input
    this->TargetTemperatureLevel = TargetTemperatureLevel;
    for( int index=0; index<plotDataSize; ++index )
    {
        xTargetTemperatureData[index] = index;
        yTargetTemperatureData[index] = TargetTemperatureLevel ;
    }
    TargetTemperatureCurve->setSamples(xTargetTemperatureData, yTargetTemperatureData, plotDataSize);
    TemperaturePlot->replot();
    TemperaturePlot->show();
}
void Window::setLightTarget(int TargetLightLevel)
{
    // for example purposes just change the amplitude of the generated input
    this->TargetLightLevel = TargetLightLevel;
    for( int index=0; index<plotDataSize; ++index )
    {
        xTargetLightData[index] = index;
        yTargetLightData[index] = TargetLightLevel ;
    }
    TargetLightCurve->setSamples(xTargetLightData, yTargetLightData, plotDataSize);
    LightPlot->replot();
    LightPlot->show();
}

void Window::modetoggle()
{
    currentmode = !currentmode;
    //ExitButton->setEnabled(currentmode);
    ManualWaterTrigger->setEnabled(currentmode);
    ManualTemperatureTrigger->setEnabled(currentmode);
    ManualLightTrigger->setEnabled(currentmode);
    TargetWaterDisplay->setDisabled(currentmode);
    TargetTemperatureDisplay->setDisabled(currentmode);
    TargetLightDisplay->setDisabled(currentmode);

    if(currentmode==true){
        ModeTextLabel2->setText("Manual");
    }
    else{
        ModeTextLabel2->setText("Auto");
    }


}

