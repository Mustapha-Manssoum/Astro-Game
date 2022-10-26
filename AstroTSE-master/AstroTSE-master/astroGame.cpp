#include "astroGame.h"
using namespace std;
using namespace cv;
MyWidget::MyWidget(QOpenGLWidget * parent):QOpenGLWidget(parent)
{
    /* Window settings */
    setFixedSize(W, H);
    m_AnimationTimer = new QTimer(this);
    //Create and set timer
    m_AnimationTimer->setInterval(10);
    connect(m_AnimationTimer, SIGNAL(timeout()),this, SLOT(Refresh()));
    m_AnimationTimer->start();

    /* Define space */
    space = new Space();
    //asteroid = new Asteroid();

    /* Initialize arrays of pointers of asteroids */
    asteroids = new Asteroid*[NB_ASTEROIDS];


    /* Initialize space */
    spaceship = new SpaceShip();

    /* Initialize space station */
    stationTSE = new SpaceStation();

    /* Generate random seed */
    srand(time(0));

    /* Generate asteroids and fill array */
    for(unsigned int i = 0; i < NB_ASTEROIDS; i++) GenerateAsteroid(i);


    /* Camera */

    cap = VideoCapture(0); // open the default camera
    cout<<"width :"<<cap.get(CAP_PROP_FRAME_WIDTH)<<endl;
    cout<<"height :"<<cap.get(CAP_PROP_FRAME_HEIGHT)<<endl;
    cap.set(CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT,frameHeight);

    if(!cap.isOpened()) { // check if we succeeded
        cerr << "Error openning the default camera" << endl;
    }

    if( !palm_cascad.load( pathToXmlPaml ) )
    {
        cerr << "Error loading haarcascade, remember to change the file path" << endl;
        exit(0);
    }

    if( !fist_cascade.load( pathtoXmlClosedPalm ) )
    {
        cerr << "Error loading haarcascade, remember to change the file path" << endl;
        exit(0);
    }

//    Initiliaze output window for the camera

    camFrame = new QLabel(this);
    camFrame->resize(2*width()/5,1*height()/5);
    camFrame->move(width()/2-camFrame->width()/2,height()-camFrame->height());

    timer = new QElapsedTimer();
    timer->start();
}

/**
 * Overriding OpenGL initialization method
 */
void MyWidget::initializeGL(){

    /* Change background color */
    glClearColor(0.5f,0.5f,0.5f,1.0f); // grey

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                           // Load identity matrix and set it as current.
    gluPerspective(70.f, 1, 0.1f, 500.f);

    /* Light activation */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


    //Ambiant light
    GLfloat light_color_tab[] = { 1.f, 1.f, 1.f, 0.f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color_tab);

    GLfloat light_tab[] = { 0.f, 2.f, 0.f, 1.f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_tab);

}

void MyWidget::paintEvent(QPaintEvent *)
{


    QPainter painter(this);
    painter.beginNativePainting();


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    CAM_POS[0] = (30) * sin(phi*M_PI/180) * cos(teta*M_PI/180) + 35 * sin(teta*M_PI/180) * sin(phi*M_PI/180);
    CAM_POS[1] = -(30) * sin(teta*M_PI/180) + 35 * cos(teta*M_PI/180);
    CAM_POS[2] = (30) * cos(phi*M_PI/180) * cos(teta*M_PI/180) + 35 * sin(teta*M_PI/180) * cos(phi*M_PI/180);


    CAM_TARGET[0]=X-CAM_POS[0];
    CAM_TARGET[1]=Y-CAM_POS[1];
    CAM_TARGET[2]=Z-CAM_POS[2];

    /* Set camera
    camX camY camZ targetX targetY targetZ vecX vecY vecZ. */
    gluLookAt(CAM_POS[0]+X, CAM_POS[1]+Y, CAM_POS[2]+Z,CAM_TARGET[0],CAM_TARGET[1],CAM_TARGET[2],0.,1.,0.);
    //gluLookAt(0.0f, 0.0f, 60.0f,0.f,0.f,0.f,0.f,1.f,0.f);

//    Display space
    space->Display(m_TimeElapsed);


//    Display Asteroids with random radius and position
    DisplayAsteroids();


//    Display the spaceship

    spaceship->Display(X,Y,Z,teta,phi);

//    Display the space station
    stationTSE->Display();

//    Display the timer
    DisplayTimer();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    painter.endNativePainting();
    glDisable(GL_DEPTH_TEST);

//    Display the camera
    displayCamera();

//    check if there is a collision
    for(unsigned int i = 0; i < NB_ASTEROIDS; i++)
    {
        // If there is a collision
        if((abs(X - (float)asteroids[i]->GetX()) <= 1.15*(float)asteroids[i]->GetRadius())
                && (abs(Z - (float)asteroids[i]->GetZ()) <= 1.75*(float)asteroids[i]->GetRadius())
                && (abs(Y - (float)asteroids[i]->GetY()) <= (float)asteroids[i]->GetRadius()))
        {
            cout<<"COLLISION !!"<<endl;
            GameOver(0); // lost
        }
    }
    if(Z <= -320) // If the spaceship arrived to space station
        GameOver(1); // won

}

//  Refresh the window

void MyWidget::Refresh(){
    m_TimeElapsed += 1.0f;
    GENERATED_ASTEROIDS=true;
    update();
}
void MyWidget::GenerateAsteroid(unsigned int i){
//  Create asteroid and set its random position.
    Asteroid * astr = new Asteroid();
//  Fill the array.
    *(asteroids + i) = astr;
}

void MyWidget::DisplayAsteroids(){
    int X=-100;
    int Y ;
    int Z=-30;
    int min = -280;
    int max = -20;
    if(GENERATED_ASTEROIDS==0){
        for(unsigned int i = 0; i < NB_ASTEROIDS; i++) {
                // generate a random x, y, z coordinates
                // pass them to display for the translate position function

                X += 10; // To avoid superposition between asteroids
                Y = (-20 + rand() % (  40 + 1 )) ; // generate random numbers between -20 and 20
                Z = (min + rand() % ( max - min + 1 )) ; // generate random numbers between min and max

                // generate a random radius between 5 and 16
                int radius = 5 + rand() % 12 ;

//          Get asteroid in array.
            Asteroid * currentAstr = *(asteroids + i);
            currentAstr->SetX(X);
            currentAstr->SetY(Y);
            currentAstr->SetZ(Z);
            currentAstr->SetRadius(radius);
            currentAstr->Display(radius, X, Y, Z);
         }
    }

//    Display Asteroids
    else{
        for(unsigned int i = 0; i < NB_ASTEROIDS; i++) {

            Asteroid * currentAstr = *(asteroids + i);
            currentAstr->Display(currentAstr->GetRadius(),currentAstr->GetX(), currentAstr->GetY(), currentAstr->GetZ());
         }
    }
}
void MyWidget::keyPressEvent(QKeyEvent * event)
{
//    Use keyboard to play

    switch(event->key())
    {
        case Qt::Key_Up:

            teta+= 3;

        break;

        case Qt::Key_Down:
            teta-=3;
        break;

        case Qt::Key_Z:
        Z -= 3;
        cout<<"Neutrale Position"<<endl;
        break;

        case Qt::Key_Left:
        cout<<"TURN LEFT"<<endl;
        phi+=1;
        X-=2;
        Z-=2;
        break;

        case Qt::Key_Right:
        cout<<"TURN RIGHT"<<endl;

        phi-=1;
        X+=2;
        Z-=1;
        break;
        case Qt::Key_Q:
            close();
            exit(0);
        break;
        case Qt::Key_R:
             X = 0;
             Y = 10;
             Z = 70;
             teta = 0;
             phi = 0;
            GENERATED_ASTEROIDS = 0;
            m_AnimationTimer->start();
            timer->restart();
            DisplayAsteroids();
            break;

        default:
            {
                // Ignore the event
                event->ignore();
                return;
            }
    }
    // Accept the event and update the scene
    if(m_AnimationTimer->isActive())
    {
        event->accept();
        update();
    }
}

void MyWidget::displayCamera() {


        Mat frame,frame_gray;
        vector<Rect> palms;
        vector<Rect> fists;

        cap >> frame; // Get frame
        cv::flip(frame,frame,1); // Mirror effect

        // Convert to gray
        cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
        // Equalize graylevels
        equalizeHist( frame_gray, frame_gray );
        //-- Detect palms
        palm_cascad.detectMultiScale( frame_gray, palms, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(20, 100) );
        if (palms.size()>0)
        {
            // Draw green rectangle
            for (int i=0;i<(int)palms.size();i++)
                rectangle(frame,palms[i],Scalar(0,255,0),2);
        }
        else

        fist_cascade.detectMultiScale( frame_gray, fists, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(80, 100) );

        // Detect closed frontal palm
        if (fists.size() == 1){
            rectangle(frame,fists[0],Scalar(255,0,0),2); // draw a blue rectangle

        }
        else if (fists.size() == 2){
//            if 2 closed frontal palms are detected, distinguish between left and right hand
            Point P_left;
            Point P_right;
            if(fists[0].x < fists[1].x)
            {
                P_left.x = fists[0].x;
                P_left.y = fists[0].y;
                P_right.x = fists[1].x;
                P_right.y = fists[1].y;
            }
            else
            {
                {
                    P_left.x = fists[1].x;
                    P_left.y = fists[1].y;
                    P_right.x = fists[0].x;
                    P_right.y = fists[0].y;
                }
            }
//            if the right hand is above the left hand (with a margin of error of +- 20) turn left
            if ( P_right.y > P_left.y + 20 ){
                rectangle(frame,fists[0],Scalar(0,255,0),2); // draw a green rectangle
                rectangle(frame,fists[1],Scalar(0,0,255),2); // draw a red rectangle
                cout<<"TURN RIGHT"<<endl;

                phi-=1;
                X+=2;
//                X = cos(phi*M_PI/180) * X + sin(phi*M_PI/180) * Z;
//                Z = -sin((phi*M_PI)/180) * X + cos(phi*M_PI/180) * Z;

                Z-=1;

            }
//            if the left hand is above the right hand (with a margin of error of +- 20) turn right
            else if ( P_left.y > P_right.y + 20 ) {
                rectangle(frame,fists[1],Scalar(0,255,0),2); // draw a green rectangle
                rectangle(frame,fists[0],Scalar(0,0,255),2); // draw a red rectangle
                cout<<"TURN LEFT"<<endl;
                phi+=1;
                X-=2;
//                X = cos(phi*M_PI/180)*X + sin(phi*M_PI/180)*Z;
//                Z = -sin(phi*M_PI/180)*X + cos(phi*M_PI/180)*Z;
                Z-=2;

            }
            else{

                    rectangle(frame,fists[1],Scalar(255,0,0),2); // draw a blue rectangle
                    rectangle(frame,fists[0],Scalar(255,0,0),2); // draw a blue rectangle


                    if( P_left.y < 100 && P_right.y < 100 )
                    {
                        teta+=1;
                        cout<<"Positive rotation"<<endl;
                    }
                    else if(P_left.y>300 && P_right.y>300)
                    {
                        teta-= 1;
                        cout<<"Negative rotation"<<endl;
                    }
                    else
                    {

                        Z -= 3;
                        cout<<"Neutrale Position"<<endl;
                    }

                    cout<<"P_left.y : "<<P_left.y<<endl;
                    cout<<"P_right.y : "<<P_right.y<<endl;
            }
            cout<<"X : "<<X<<"   Y : "<<Y<<"   Z : "<<Z<<endl;
        }


//        Displays frame
        Mat displayFrame;
        frame.copyTo(displayFrame);

        QImage qImage(displayFrame.data, displayFrame.cols, displayFrame.rows, displayFrame.step, QImage::Format_BGR888);
        QPixmap qPix = QPixmap::fromImage(qImage);

        camFrame->setPixmap(qPix.scaled(camFrame->width(), camFrame->height(), Qt::KeepAspectRatio));
    }

void MyWidget::GameOver(BOOL WonOrLost)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::gray);
    QRectF rectangle(width() / 3, height()/3, width()/2, height()/3);
    painter.drawRoundedRect(rectangle, 20.0, 15.0);

    if(!WonOrLost) // Lost (crash on an asteroid)
    {
        QFont font("Monospace", 30); //Police "Monospace", size = 30
        painter.setPen(Qt::red);
        painter.setFont(font);
        painter.drawText(width() / 3, height() / 2, QString("Colision ! You failed"));
    }
    else // Won (Arrive to the space station successfully
    {
        QFont font("Monospace", 30);
        painter.setPen(Qt::green);
        painter.setFont(font);
        painter.drawText(width() / 3, height() / 2, QString("Congratulations ! You Won"));
    }

    QFont font2("Monospace", 15);
    painter.setPen(Qt::white);
    painter.setFont(font2);
    painter.drawText(width() / 3, 3*height() /5, QString("Press Q to quit"));

    QFont font3("Monospace", 15);
    painter.setPen(Qt::blue);
    painter.setFont(font2);
    painter.drawText(width() / 3, 3*height() /8, QString("Press R to Restart"));
    painter.end();
    m_AnimationTimer->stop();
}

void MyWidget::DisplayTimer()
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::green);

    QFont font("Times", 15, QFont::Bold);
    painter.setFont(font);

    painter.drawText(Qt::AlignRight, height() / 20, QString("Timer : ") + QString::number(timer->elapsed() / 1000) + QString(" sec"));

    painter.end();
}



MyWidget::~MyWidget()
{
    delete[] asteroids;
    delete m_AnimationTimer;
    delete timer;
    delete[] CAM_POS;
    delete[] CAM_TARGET;
    delete camFrame;
}

