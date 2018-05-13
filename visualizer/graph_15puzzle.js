function loadCSV(targetFile) {
 
    // 読み込んだデータを1行ずつ格納する配列
    var allData = [];
 
    // XMLHttpRequestの用意
    var request = new XMLHttpRequest();
    request.open("get", targetFile, false);
    request.send(null);
 
    // 読み込んだCSVデータ
    var csvData = request.responseText;
 
    // CSVの全行を取得
    var lines = csvData.split("\n");
 
    for (var i = 0; i < (lines.length - 1); i++) {
        // 1行ごとの処理
 
        var wordSet = lines[i].split(",");
 
        var wordData = {
            label: i,
            y: parseFloat(wordSet[0]),
        };
        // if (i == lines.length - 1) {break;}
 
        allData.push(wordData);
    }
    return allData;
}


window.onload = function () {
  var bpida = loadCSV("../results/15puzzle_bpida_korf100.txt");
  var bpida_find_all = loadCSV("../results/15puzzle_bpida_findall_korf100.txt");
  var bpida_global = loadCSV("../results/15puzzle_bpida_global_korf100.txt");
  var bpida_global_find_all = loadCSV("../results/15puzzle_bpida_global_findall_korf100.txt");

  var chart = new CanvasJS.Chart("chartContainer",
  {
    title:{
      text: "Result of BPIDA* in Kolf's 100 problems"             
    }, 
    animationEnabled: true,     
    axisY:{
      titleFontFamily: "arial",
      titleFontSize: 12,
      includeZero: false
    },
    toolTip: {
      shared: true
    },
    data: [
    {        
      type: "line",  
      name: "BPIDA*" ,      
      showInLegend: true,
      dataPoints: bpida
    },
    {        
      type: "line",  
      name: "BPIDA*(find all)",        
      showInLegend: true,
      dataPoints: bpida_find_all
    },
    {        
      type: "line",  
      name: "BPIDA*Global",        
      showInLegend: true,
      dataPoints: bpida_global
    },
    {        
      type: "line",  
      name: "BPIDA*Global(find all)",        
      showInLegend: true,
      dataPoints: bpida_global_find_all
    }        
    ],
    legend:{
      cursor:"pointer",
      itemclick:function(e){
        if(typeof(e.dataSeries.visible) === "undefined" || e.dataSeries.visible) {
          e.dataSeries.visible = false;
        }
        else {
          e.dataSeries.visible = true;            
        }
        chart.render();
      }
    }
  });
  chart.render();
}
