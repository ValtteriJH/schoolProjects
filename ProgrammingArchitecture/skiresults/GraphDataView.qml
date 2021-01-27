import QtQuick 2.0
import QtQuick.Controls 2.2
import QtCharts 2.0
//import qt.chart 1.0

Item {


    id: chartroot
    width: parent.width
    height: parent.height
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter

    ChartView {
        id: chart
        anchors.fill: parent
        antialiasing: true
        axes: [

            ValueAxis {
                id: axisX
                min: 0
                max: 10000
            },

            ValueAxis {
                id: axisY
                min: 0
                max: 10000
            }
        ]
    }

    function addLines(data)
    {
        chart.removeAllSeries();

        var firstvalue = parseInt(data[0][1]);
        var lastindex = data[0].length - 1;
        var lastvalue = parseInt(data[0][lastindex]);

        axisX.min = firstvalue;
        axisX.max = lastvalue;
        axisX.tickCount = lastvalue - firstvalue + 1;

        for(var i in data)
        {
            if(i != 0)
            {
                var series = chart.createSeries(ChartView.SeriesTypeLine, data[i][0], axisX, axisY);
                series.pointsVisible = true;
                series.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
                var longestTime = 0;
                for(var j in data[i])
                {
                    if(j == 0)
                    {
                        continue;
                    }

                    var time = data[i][j];
                    var hours = 0;
                    var minutes = 0;
                    var seconds = 0;
                    if(time !== "")
                    {
                        hours = time.substring(0,2);
                        minutes = time.substring(3,5);
                        seconds = time.substring(6,8);
                    }
                    var x = firstvalue + parseInt(j) - 1;
                    var y = parseInt(hours) + (parseInt(minutes)/60) + (parseInt(seconds)/120);
                    if(y > longestTime)
                    {
                        longestTime = y;
                    }
                    series.append(x, y);
                }
            }
        }
        axisY.max = longestTime + 0.5;
    }
    Connections {
        target: chartmodel
        onSendData: {
            addLines(data);
        }
    }
}
