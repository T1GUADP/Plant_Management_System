#include "window.h"
// #include "adcreader.h"

#include <cmath>  // for sine stuff


Window::Window() : gain(5), count(0)
{
    //first row Interactables
    ModeButton = new QPushButton;
    ModeButton->setText("Toggle Mode");
    ModeTextLabel1 = new QLabel;
    ModeTextLabel1->setText("Current Mode: ");
    ModeTextLabel2 = new QLabel;
    ModeTextLabel2->setText("Placeholder");
    ExitButton = new QPushButton;
    ExitButton->setText("Exit Program");
    //firstrow layout
    gLayout = new QGridLayout;
    gLayout->addWidget(ModeButton,0,0,Qt::AlignLeft);
    gLayout->addWidget(ModeTextLabel1,0,1,Qt::AlignLeft);
    gLayout->addWidget(ModeTextLabel2,0,2,Qt::AlignLeft);
    gLayout->addWidget(ExitButton,0,4,Qt::AlignRight);
    //Second row Interactables
    //PresetComboBox = new QComboBox;//
    Placeholder = new QPushButton;
    Placeholder->setText("Placeholder");
    ApplyButton = new QPushButton;
    ApplyButton->setText("Apply");
    NewEntryButton = new QPushButton;
    NewEntryButton->setText("New Entry");
    DeleteEntryButton = new QPushButton;
    DeleteEntryButton->setText("Delete Entry");
    ModifyButton = new QPushButton;
    ModifyButton->setText("Modify Current");
    //Second row layout
    gLayout->addWidget(Placeholder,1,0,Qt::AlignLeft);
    gLayout->addWidget(ApplyButton,1,1,Qt::AlignLeft);
    gLayout->addWidget(NewEntryButton,1,2,Qt::AlignLeft);
    gLayout->addWidget(DeleteEntryButton,1,3,Qt::AlignLeft);
    gLayout->addWidget(ModifyButton,1,4,Qt::AlignRight);
    //Third row Interactables
    WaterPlot =new QwtPlot;
    Watercurve = new QwtPlotCurve;
    //WaterVerticalSlider = new QSLIDER_V;
    TemperaturePlot =new QwtPlot;
    Temperaturecurve = new QwtPlotCurve;
    //TemperatureVerticalSlider
    LightPlot = new QwtPlot;
    Lightcurve = new QwtPlotCurve;
    //LightVerticalSlider
    //Third row layout
    hLayout = new QHBoxLayout;
    hLayout->addWidget(WaterPlot);
    hLayout->addWidget(TemperaturePlot);
    hLayout->addWidget(LightPlot);
    //Fourth row layout



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
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
    // for example purposes just change the amplitude of the generated input
    this->gain = gain;
}
