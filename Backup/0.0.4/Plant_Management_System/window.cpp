#include "window.h"
// #include "adcreader.h"

#include <cmath>  // for sine stuff


Window::Window() : gain(5), count(0)
{
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
    //PresetComboBox = new QComboBox;//will contain target presets for water, light and temperature
    Placeholder = new QPushButton; //Placeholder for PresetComboBox
    Placeholder->setText("Placeholder");
    ApplyButton = new QPushButton; //Will apply the selected preset
    ApplyButton->setText("Apply");
    NewEntryButton = new QPushButton; //Will add new entry to the preset list based on current values
    NewEntryButton->setText("New Entry");
    DeleteEntryButton = new QPushButton; //Will delete currently selected entry
    DeleteEntryButton->setText("Delete Entry");
    ModifyButton = new QPushButton; //Will modify currently selected entry with changed values (currently selected)
    ModifyButton->setText("Modify Current");
    //Second row layout (adds widgets to gridlayout)
    gLayout->addWidget(Placeholder,1,0,Qt::AlignLeft);
    gLayout->addWidget(ApplyButton,1,1,Qt::AlignCenter);
    gLayout->addWidget(NewEntryButton,1,2,Qt::AlignCenter);
    gLayout->addWidget(DeleteEntryButton,1,3,Qt::AlignCenter);
    gLayout->addWidget(ModifyButton,1,4,Qt::AlignRight);
    //Third row Interactables
    WaterPlot =new QwtPlot; //Creates new plot
    Watercurve = new QwtPlotCurve; //Assignes curve to plot
    TemperaturePlot =new QwtPlot;
    Temperaturecurve = new QwtPlotCurve;
    TargetTemperaturecurve = new QwtPlotCurve;
    LightPlot = new QwtPlot;
    Lightcurve = new QwtPlotCurve;
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
            yData[index] = gain * sin( M_PI * index/50 );
        }

        curve = new QwtPlotCurve;
        plot = new QwtPlot;
        // make a plot curve from the data and attach it to the plot
        curve->setSamples(xData, yData, plotDataSize);
        curve->attach(plot);
        Watercurve->setSamples(xData, yData, plotDataSize);
        Watercurve->attach(WaterPlot);
        Temperaturecurve->setSamples(xData, yData, plotDataSize);
        Temperaturecurve->attach(TemperaturePlot);



        Lightcurve->setSamples(xData, yData, plotDataSize);
        Lightcurve->attach(LightPlot);
        plot->replot();
        plot->show();
        WaterPlot->replot();
        WaterPlot->show();
        TemperaturePlot->replot();
        TemperaturePlot->show();
        LightPlot->replot();
        LightPlot->show();


        // set up the layout - knob above thermometer
        vLayout = new QVBoxLayout;
        vLayout->addWidget(knob);
        vLayout->addWidget(thermo);

        // plot to the left of knob and thermometer
        hLayout1 = new QHBoxLayout;
        hLayout1->addLayout(vLayout);
        hLayout1->addWidget(plot);

        VLayout1 = new QVBoxLayout;
        VLayout1->addLayout(gLayout);
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
//	adcreader->quit();
    // wait until the run method has terminated
//	adcreader->wait();
//	delete adcreader;
}

void Window::timerEvent( QTimerEvent * )
{
    double inVal = gain * sin( M_PI * count/50.0 );

    ++count;

    // add the new input to the plot
    memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
    yData[plotDataSize-1] = inVal;
    curve->setSamples(xData, yData, plotDataSize);
    Watercurve->setSamples(xData, yData, plotDataSize);
    Temperaturecurve->setSamples(xData, yData, plotDataSize);
    Lightcurve->setSamples(xData, yData, plotDataSize);


    plot->replot();
    WaterPlot->replot();
    TemperaturePlot->replot();
    LightPlot->replot();

    // set the thermometer value
    thermo->setValue( inVal + 10 );
    //update "Current:" values in the fifth row
    CurrentWaterDisplay-> setText(QString::number(round(inVal*10)/10));
    CurrentTemperatureDisplay-> setText((QString::number(round(inVal*10)/10))+"C");
    CurrentLightDisplay-> setText(QString::number(round(inVal*10)/10));


}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
    // for example purposes just change the amplitude of the generated input
    this->gain = gain;
}



    bool currentmode = true;

void Window::modetoggle()
{
    currentmode = !currentmode;
    ExitButton->setEnabled(currentmode);
    if(currentmode==true){
        ModeTextLabel2->setText("Auto");
    }
    else{
        ModeTextLabel2->setText("Manual");
    }


}

