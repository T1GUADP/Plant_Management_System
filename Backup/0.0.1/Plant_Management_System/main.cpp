    #include <QApplication>
    #include <QPushButton>
    #include <QHBoxLayout>
    #include <QVBoxLayout>
    #include <QTabBar>
    #include <QTabWidget>
    #include <QSpacerItem>
    #include <QGridLayout>
    #include <QSizePolicy>

    int main(int argc, char *argv[])
    {
        //Starting application loop
        QApplication app(argc, argv);

                //Creating Winfow
                QWidget *window= new QWidget;

                //Setting title
                window->setWindowTitle("PlantManagementSystem");

                //Creating GUI elements
                QPushButton *ModeToggleButton=new QPushButton("");
                QSpacerItem *ModeToggleSpacer=new QSpacerItem(50, 20);
                QTabWidget *tabs=new QTabWidget(window);

                //QWidget *centralWidget = new QWidget(window);
                //QTabWidget *tabs=new QTabWidget(centralWidget);


                //tabs->setFixedSize(245, 245);
                tabs->addTab(new QWidget(),"TAB 1");
                tabs->addTab(new QWidget(),"TAB 2");
                tabs->addTab(new QWidget(),"TAB 3");

                //Creating Layout
                QGridLayout *glayout = new QGridLayout;
                QHBoxLayout *hlayout = new QHBoxLayout;
                QVBoxLayout *vlayout = new QVBoxLayout;


                //Setting main window size policy
                window->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
                window->setMinimumSize(200,200);
                QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                sizePolicy.setHorizontalStretch(1);
                sizePolicy.setVerticalStretch(1);
                window->setSizePolicy(sizePolicy);

                //Adding the button to the gridlayout

                hlayout->addWidget(ModeToggleButton);
                hlayout->addItem(ModeToggleSpacer);
                //hlayout->addWidget(ModeToggleSpacer);
                vlayout->addLayout(hlayout);
                vlayout->addWidget(tabs);
                //settingWindow's layout
                window->setLayout(vlayout);

                window->show();




        return app.exec();
    }
