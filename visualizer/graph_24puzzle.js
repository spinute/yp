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
  var bpida = loadCSV("../results/yama24_50_hard_new_bpida5");
  var bpida_fa = loadCSV("../results/yama24_50_hard_new_bpida5_fa");
  var bpida_global = loadCSV("../results/yama24_50_hard_new_bpida5_global");
  var bpida_global_fa = loadCSV("../results/yama24_50_hard_new_bpida5_global_fa");

  var c5 = loadCSV("../results/yama24_50_hard_new_c5");
  var c5_fa = loadCSV("../results/yama24_50_hard_new_c5_fa");

  var bpida_pdb = loadCSV("../results/yama24_50_hard_new_bpida5_pdb");
  var bpida_pdb_fa = loadCSV("../results/yama24_50_hard_new_bpida5_pdb_fa");
  var bpida_pdb_global = loadCSV("../results/yama24_50_hard_new_bpida5_pdb_global");
  var bpida_pdb_global_fa = loadCSV("../results/yama24_50_hard_new_bpida5_pdb_global_fa");

  var c5_pdb = loadCSV("../results/yama24_50_hard_new_c5_pdb");
  var c5_pdb_fa = loadCSV("../results/yama24_50_hard_new_c5_pdb_fa");

  var korf24_bpida_pdb = loadCSV("../results/korf-24-easy10_bpida5_pdb");
  var korf24_bpida_pdb_fa = loadCSV("../results/korf-24-easy10_bpida5_pdb_fa");
  var korf24_bpida_pdb_global = loadCSV("../results/korf-24-easy10_bpida5_pdb_global");
  var korf24_bpida_pdb_global_fa = loadCSV("../results/korf-24-easy10_bpida5_pdb_global_fa");

  var korf24_c5_pdb = loadCSV("../results/korf-24-easy10_c5_pdb");
  var korf24_c5_pdb_fa = loadCSV("../results/korf-24-easy10_c5_pdb_fa");

  var chart = new CanvasJS.Chart("chartContainer",
  {
    title:{
      text: "Executed Time of BPIDA* in yama's 50 problems"             
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
      dataPoints: c5
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
      text: "Executed Time of BPIDA*(Find all) in yama's 50 problems"             
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
      dataPoints: c5_fa
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

  var chart_pdb = new CanvasJS.Chart("chartContainerPDB",
  {
    title:{
      text: "Executed Time of BPIDA*(PDB) in yama's 50 problems"             
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
      dataPoints: c5_pdb
    },
    {        
      type: "line",  
      name: "BPIDA*" ,      
      showInLegend: true,
      dataPoints: bpida_pdb
    },
    {        
      type: "line",  
      name: "BPIDA*Global",        
      showInLegend: true,
      dataPoints: bpida_pdb_global
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
        chart_pdb.render();
      }
    }
  });
  chart_pdb.render();

  var chart_pdb_FA = new CanvasJS.Chart("chartContainerPDBFA",
  {
    title:{
      text: "Executed Time of BPIDA*(PDB Find all) in yama's 50 problems"             
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
      dataPoints: c5_pdb_fa
    },
    {        
      type: "line",  
      name: "BPIDA*(find all)",        
      showInLegend: true,
      dataPoints: bpida_pdb_fa
    },
    {        
      type: "line",  
      name: "BPIDA*Global(find all)",        
      showInLegend: true,
      dataPoints: bpida_pdb_global_fa
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
        chart_pdb_FA.render();
      }
    }
  });
  chart_pdb_FA.render();

  var chart_pdb_hard = new CanvasJS.Chart("chartContainerPDBHARD",
  {
    title:{
      text: "Executed Time of BPIDA*(PDB) in Korf's 10 problems"             
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
      dataPoints: korf24_c5_pdb
    },
    {        
      type: "line",  
      name: "BPIDA*" ,      
      showInLegend: true,
      dataPoints: korf24_bpida_pdb
    },
    {        
      type: "line",  
      name: "BPIDA*Global",        
      showInLegend: true,
      dataPoints: korf24_bpida_pdb_global
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
        chart_pdb_hard.render();
      }
    }
  });
  chart_pdb_hard.render();

  var chart_pdb_FA_hard = new CanvasJS.Chart("chartContainerPDBFAHARD",
  {
    title:{
      text: "Executed Time of BPIDA*(PDB Find all) in Korf's 10 problems"             
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
      dataPoints: korf24_c5_pdb_fa
    },
    {        
      type: "line",  
      name: "BPIDA*(find all)",        
      showInLegend: true,
      dataPoints: korf24_bpida_pdb_fa
    },
    {        
      type: "line",  
      name: "BPIDA*Global(find all)",        
      showInLegend: true,
      dataPoints: korf24_bpida_pdb_global_fa
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
        chart_pdb_FA_hard.render();
      }
    }
  });
  chart_pdb_FA_hard.render();

  // var bpida_global_fa = loadCSV("../results/yama24_50_hard_new_bpida5_global_fa");
  var bpida_global_fa_8720 = loadCSV("../results/yama24_50_hard_new_bpida5_global_sh_fa_8720");
  var bpida_global_fa_4312 = loadCSV("../results/yama24_50_hard_new_bpida5_global_sh_fa_4312");
  var bpida_global_fa_35168 = loadCSV("../results/yama24_50_hard_new_bpida5_global_sh_fa_35168");
  var bpida_global_fa_13128 = loadCSV("../results/yama24_50_hard_new_bpida5_global_sh_fa_13128");
  var bpida_global_fa_17536 = loadCSV("../results/yama24_50_hard_new_bpida5_global_sh_fa_17536");

  var chartFASHARD = new CanvasJS.Chart("chartContainerFASHARED",
  {
    title:{
      text: "Executed Time of BPIDA*(Find all) in yama's 50 problems"             
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
      name: "BPIDA*Global(find all)",        
      showInLegend: true,
      dataPoints: bpida_global_fa
    },
    {        
      type: "line",  
      name: "BPIDA*Global(find all) 4312 byte",        
      showInLegend: true,
      dataPoints: bpida_global_fa_4312
    },
    {        
      type: "line",  
      name: "BPIDA*Global(find all) 8720 byte",        
      showInLegend: true,
      dataPoints: bpida_global_fa_8720
    },
    {        
      type: "line",  
      name: "BPIDA*Global(find all) 13128 byte",        
      showInLegend: true,
      dataPoints: bpida_global_fa_13128
    },
    {        
      type: "line",  
      name: "BPIDA*Global(find all) 17536 byte",        
      showInLegend: true,
      dataPoints: bpida_global_fa_17536
    },    
    {        
      type: "line",  
      name: "BPIDA*Global(find all) 35168 byte",        
      showInLegend: true,
      dataPoints: bpida_global_fa_35168
    },               
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
        chartFASHARD.render();
      }
    }
  });
  chartFASHARD.render();
}
