///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////

import QtQuick 2.15
import QtQuick.Window 2.15
import QtMultimedia 5.15
import QtQuick.Controls 2.15
import MDKPlayer 1.0
//Qml of video player GUI

ApplicationWindow {
    id:mainWindow
    visible: true

    // initial window size at ratio of 16:10
    width: 720
    height: 450

    // window title [ignore warning don't worry it wotks]
    title: qsTr("The Video Player")

    // playbackMuted is used to store mute value
    property bool playbackMuted: false
    property var seekWidth: calcSeekerWidth()
    ///////////////////////////////////////////////////////////////////////
    // enable double click on any point to full screen
    MouseArea{
        anchors.fill: parent
        onDoubleClicked:{
            fullScreenToggle();
        }
    }
    ////////////////////////////////////////////////////////////////////////
    // signal connect :)
    Component.onCompleted: {

        // this signal is triggered when a we need to set a new video url
        PlayerEngine.onPlayNow.connect(playNow)

        // this signal is triggered when a we need to set a new video url and show window if minimized
        SingleInstance.onDoAction.connect(showNow)
    }

    ///////////////////////// js code ///////////////////////////////////////

    // js function to toggle full screen on user request
    function fullScreenToggle(){
        if(mainWindow.visibility !== Window.Windowed) // if fullscreen
            mainWindow.visibility = Window.Windowed; // make it normal window
        else
            mainWindow.visibility = Window.FullScreen;//make it fullscreen
    }

    // js function to toggle mute
    function muteToggle(){
        playbackMuted = !playbackMuted; // invert the mute var
        mediaPlayer.mute(playbackMuted); // set mediaplayer to mute state
    }

    // js code to auto hide the playPauseButton after a timout
    function onHidePlayPauseButton(){
        fadeout.start();
    }

    // js code to set url and restore from minimized
    function showNow(){
        mainWindow.visibility = Window.Windowed;
    }

    // js function to calculate seeker width
    function calcSeekerWidth(){
        return mediaPlayer.duration() > 0? progressBar.width * mediaPlayer.position() / mediaPlayer.duration() : 0
    }

    // js function to toggle playback

    function playPause(){
        if(mediaPlayer.isPlaying()){
            mediaPlayer.pause();
            playPauseButton.opacity = 1;
            seekbarUpdateTimer.stop();
        }else{
            mediaPlayer.play();
            fadeout.start();
            seekbarUpdateTimer.start();
        }
    }

    ////////

    Timer {
        id:seekbarUpdateTimer
        interval: 1000; running: true; repeat: true
        onTriggered: {
            seekWidth = calcSeekerWidth()
        }
    }


    ///////



    /////////////////////////////////////////////////////////////////////////////////////
    //                                                                                 //
    //                          The PlayPauseButton Code                               //
    //                                                                                 //
    /////////////////////////////////////////////////////////////////////////////////////

    RoundButton{
        id              : playPauseButton
        z               : 100 // make it just above the video so it wil be always visible
        anchors.centerIn: parent
        visible         : true // yay
        enabled         : true // clickable
        radius          : 128  //
        height          : 128  //
        width           : 128  //
        opacity         : 0
        focus           : true // so it catched key events

        icon.color      : "transparent" // cool
        icon.source     : "qrc:/images/playPauseIcon.png" // I love this icon
        icon.width      : playPauseButton.width * 2 // so it fill button
        icon.height     : playPauseButton.height * 2 // I dont know why not that is the default

        // key bindings

        /* Space to play / pause playback
           it sets the playback state to the opposite of current */
        Keys.onSpacePressed: playPause();

        // seek back 5000 ms by left arrow key
        Keys.onLeftPressed: {
            mediaPlayer.seek(mediaPlayer.position() -10000);
            seeker.width = calcSeekerWidth();
        }
        // seek forward 5000 ms by right arrow key
        Keys.onRightPressed: {
            mediaPlayer.seek(mediaPlayer.position() + 10000);
            seeker.width = calcSeekerWidth();
        }
        // exit full screen by ESC also F key will work too.
        Keys.onEscapePressed: {
            if( mainWindow.visibility === Window.FullScreen )
                mainWindow.visibility =  Window.Windowed
        }
        // This key event handler if for both MUTE and FULL SCREEN
        Keys.onPressed: {
            if (event.key === Qt.Key_F) {
                fullScreenToggle();
                event.accepted = true;
            }
            else if (event.key === Qt.Key_M) {
                muteToggle();
                event.accepted = true;
            }

        }

        // toggle play pause when clicked on the button
        onClicked: playPause();
        // fade in and out by hovering the button
        onHoveredChanged: {
            if(hovered)
                fadeInOnStart();
            else
                fadeOutOnStart();
        }


        // js functions to start fade out
        function fadeOutOnStart(){
            if(playPauseButton.opacity)
                fadeout.start();
        }
        // js functions to start fade
        function fadeInOnStart(){
            if(!playPauseButton.opacity)
                fadein.start();
        }

        // fade in animation
        NumberAnimation {
            id: fadein
            target: playPauseButton
            property: "opacity"
            easing.type: Easing.InOutQuad
            duration: 300
            from: 0
            to: 1
        }
        // fade out animation
        NumberAnimation {
            id: fadeout
            target: playPauseButton
            property: "opacity"
            easing.type: Easing.InOutQuad
            from: 1
            to: 0
        }
    }



    /////////////////////////////////////////////////////////////////////////////////////
    //                                                                                 //
    //                          USER INTERFACE BULDING BLOCKS                          //
    //                                                                                 //
    /////////////////////////////////////////////////////////////////////////////////////


    // The VideoPlayer
    Rectangle {
        id:player
        z:99
        color: "black"
        anchors.fill: parent
        MDKPlayer {
            id: mediaPlayer
            source: PlayerEngine.m_Url
            anchors.fill: parent

            Component.onCompleted: player.play() // to early, will stopped by setSource()
        }
        // Mute icon
        Image{
            height: 32
            width: 32
            z:200
            x:32
            y:32
            visible: playbackMuted
            source:"qrc:/images/mute.png"
        }
    }

    // The ProgressBar grey frame
    Rectangle {
        id                 : progressBar
        z                  : 102
        anchors.left       : parent.left
        anchors.right      : parent.right
        anchors.bottom     : parent.bottom
        anchors.margins    : 0
        height             : 8
        color              : "Gray"

        // red ProgressBar
        Rectangle {
            id             : seeker
            anchors.left   : parent.left
            anchors.top    : parent.top
            anchors.bottom : parent.bottom
            width          : seekWidth
            color          : "red"
        }

        //clickable Event
        MouseArea {
            property int pos
            anchors.fill: parent

            onClicked: {
                pos = mouse.x / width * 1.0 * mediaPlayer.duration();
                mediaPlayer.seek(pos);
                seekWidth = calcSeekerWidth();
            }
        }
    }
}

////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
