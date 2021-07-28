import QtQuick 2.15
import QtQuick.Window 2.15
import QtMultimedia 5.15
import QtQuick.Controls 2.15

Window {
    id:mainWindow
    visible: true
    width: 720
    height: 450
    title: qsTr("The Video Player")
    property bool playbackEnabled: true
    property bool playbackMuted: false


    function fullScreenToggle(){
        if(mainWindow.visibility !== Window.Windowed){
            mainWindow.visibility = Window.Windowed;
        }else{
            mainWindow.visibility = Window.FullScreen;
        }
    }

    function muteToggle(){
        playbackMuted = !playbackMuted;
        mediaPlayer.muted = playbackMuted;
    }

    MouseArea{
        anchors.fill: parent

        onDoubleClicked:{
            fullScreenToggle();
        }

    }

    Component.onCompleted: {
        VideoCaptureDetector.onRunningScreenCapture.connect(videoCapDetectSlot)
        PlayerEngine.onPlayNow.connect(playNow)
        PlayerEngine.onHidePlayPauseButton.connect(onHidePlayPauseButton)
        SingleInstance.onDoAction.connect(showNow)
    }

    function videoCapDetectSlot(playState,screenCaptureToolName){
        if(playState){
            video.visible = true
            mediaPlayer.muted = playbackMuted
            video.z = 99
            statusText.visible = false
            statusText.text = "Video Capture Not Detected."
            playbackEnabled = true
        }
        else{
            video.visible = false
            mediaPlayer.muted = true
            video.z = 97
            statusText.visible = true
            statusText.text = "Video Capture Tool Detected. [ " + screenCaptureToolName + " ] Please close it to continue playback"
            playbackEnabled = false
        }
    }

    function onHidePlayPauseButton(){
        playPauseButton.opacity = 0;
        console.log("ok");
    }

    function showNow(_url){
        mainWindow.visibility = Window.Windowed;
        mediaPlayer.source = _url;
    }

    function playNow(_url){
        mediaPlayer.source = _url;
    }

    Rectangle {
        id:player
        x:99
        color: "black"
        anchors.fill: parent

        MediaPlayer {
            id: mediaPlayer
            autoPlay: true
            onSourceChanged: {
                mediaPlayer.play();
            }
            onStopped: {
                playPauseButton.fadeInOnStart()
            }
            onPaused: {
                playPauseButton.fadeInOnStart()
            }
            onPlaying: {
                playPauseButton.fadeOutOnStart();
            }

        }

        VideoOutput {
            id: video
            anchors.fill: parent
            source: mediaPlayer

        }
        Rectangle{
            z:98
            color: "black"
            anchors.fill: player
            Text {
                id: statusText
                text: "Detecting ..."
                color:"white"
            }
        }
        Image{
            height: 32
            width: 32
            z:200
            x:32
            y:32
            visible: playbackMuted
            source:"qrc:/mute.png"
        }
    }


    RoundButton{
        id:playPauseButton
        z:100
        icon.color: "transparent"
        icon.source: "qrc:/playPauseIcon.png"
        icon.width: playPauseButton.width
        icon.height: playPauseButton.height

        visible:true
        enabled: true
        radius: 128
        height: 128
        width:  128
        onClicked: {
            if(playbackEnabled)
                mediaPlayer.playbackState == MediaPlayer.PlayingState ? mediaPlayer.pause() : mediaPlayer.play()
            if(MediaPlayer.playbackState)
                playPauseButton.opacity=1
        }
        onHoveredChanged: {
            if(hovered)
                fadein.start()
            else
                fadeout.start()
        }

        anchors.centerIn: parent
        NumberAnimation {
            id: fadein
            target: playPauseButton
            property: "opacity"
            easing.type: Easing.InOutQuad
            duration: 300
            from: 0
            to: 1
        }
        NumberAnimation {
            id: fadeout
            target: playPauseButton
            property: "opacity"
            easing.type: Easing.InOutQuad
            from: 1
            to: 0
        }
        function fadeOutOnStart(){
            fadeout.start();
        }

        function fadeInOnStart(){
            fadein.start();
        }
        focus: true
        Keys.onSpacePressed: mediaPlayer.playbackState == MediaPlayer.PlayingState ? mediaPlayer.pause() : mediaPlayer.play()
        Keys.onLeftPressed: mediaPlayer.seek(mediaPlayer.position - 5000)
        Keys.onRightPressed: mediaPlayer.seek(mediaPlayer.position + 5000)
        Keys.onEscapePressed: {
            if( mainWindow.visibility === Window.FullScreen )
                mainWindow.visibility =  Window.Windowed
        }
        Keys.onPressed: {
            if (event.key === Qt.Key_F) {
                fullScreenToggle();
                event.accepted = true;
            }
            if (event.key === Qt.Key_M) {
                muteToggle();
                event.accepted = true;
            }

        }

    }

    Rectangle {
        z:102
        id: progressBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 0
        height: 5
        color: "Gray"

        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: mediaPlayer.duration>0?parent.width*mediaPlayer.position/mediaPlayer.duration:0
            color: "red"
        }

        MouseArea {
            property int pos
            anchors.fill: parent

            onClicked: {
                if (mediaPlayer.seekable)
                    pos = mediaPlayer.duration * mouse.x/width
                mediaPlayer.seek(pos)
            }

        }
    }
}
