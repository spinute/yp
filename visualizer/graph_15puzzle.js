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
 
        var wordSet = lines[i].split(" ");
        console.log(wordSet);
 
        var wordData = {
            label: i,
            y: parseFloat(wordSet[1]),
        };
        console.log(parseFloat(wordSet[1]));
        // if (i == lines.length - 1) {break;}
 
        allData.push(wordData);
    }
    return allData;
}


window.onload = function () {
  var bpida = loadCSV("../results/korf100_bpida4");
  var bpida_fa = loadCSV("../results/korf100_bpida4_fa");
  var bpida_global = loadCSV("../results/korf100_bpida4_global");
  var bpida_global_fa = loadCSV("../results/korf100_bpida4_global_fa");

  var c4 = loadCSV("../results/korf100_c4");
  var c4_fa = loadCSV("../results/korf100_c4_fa");

  var chart = new CanvasJS.Chart("chartContainer",
  {
    title:{
      text: "Executed Time of BPIDA* in Kolf's 100 problems"             
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
      name: "IDA* cpu",
      showInLegend: true,
      dataPoints: c4
    },
    {        
      type: "line",  
      name: "BPIDA*" ,      
      showInLegend: true,
      dataPoints: bpida
    },
    {        
      type: "line",  
      name: "BPIDA*Global",        
      showInLegend: true,
      dataPoints: bpida_global
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

  var chartFA = new CanvasJS.Chart("chartContainerFA",
  {
    title:{
      text: "Executed Time of BPIDA*(Find all) in Kolf's 100 problems"             
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
      name: "IDA* cpu(find all)",
      showInLegend: true,
      dataPoints: c4_fa
    },
    {        
      type: "line",  
      name: "BPIDA*(find all)",        
      showInLegend: true,
      dataPoints: bpida_fa
    },
    {        
      type: "line",  
      name: "BPIDA*Global(find all)",        
      showInLegend: true,
      dataPoints: bpida_global_fa
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
        chartFA.render();
      }
    }
  });
  chartFA.render();
}
