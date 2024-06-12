<Qucs Schematic 0.0.15>
<Properties>
  <View=0,0,800,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=practica2-3a.dat>
  <DataDisplay=practica2-3a.dpl>
  <OpenDisplay=1>
  <showFrame=0>
  <FrameText0=T\x00EDtulo>
  <FrameText1=Dibujado por:>
  <FrameText2=Fecha:>
  <FrameText3=Revisi\x00F3n:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <GND * 1 440 350 0 0 0 0>
  <R R1 1 550 180 -26 15 0 0 "1 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R2 1 300 180 -26 15 0 0 "2 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R3 1 160 270 15 -26 0 1 "3 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <Vdc V2 1 440 270 18 -26 0 1 "10 V" 1>
  <Vdc V1 1 660 270 18 -26 0 1 "5 V" 1>
  <.DC DC1 1 40 40 0 40 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "150" 0 "no" 0 "none" 0 "CroutLU" 0>
  <VProbe Sonda_V 1 60 210 -33 -63 1 2>
  <IProbe Sonda_I 1 160 210 16 -26 1 3>
</Components>
<Wires>
  <160 180 270 180 "" 0 0 0 "">
  <330 180 440 180 "" 0 0 0 "">
  <580 180 660 180 "" 0 0 0 "">
  <660 180 660 240 "" 0 0 0 "">
  <660 300 660 350 "" 0 0 0 "">
  <160 350 440 350 "" 0 0 0 "">
  <160 300 160 350 "" 0 0 0 "">
  <440 350 660 350 "" 0 0 0 "">
  <440 300 440 350 "" 0 0 0 "">
  <440 180 520 180 "" 0 0 0 "">
  <440 180 440 240 "" 0 0 0 "">
  <70 230 70 240 "" 0 0 0 "">
  <70 240 160 240 "" 0 0 0 "">
  <50 230 50 300 "" 0 0 0 "">
  <50 300 160 300 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Tab 150 483 251 63 3 #c0c0c0 1 00 1 0 1 1 1 0 1 1 1 0 1 1 315 0 225 "" "" "">
	<"Sonda_I.I" #0000ff 0 3 1 0 0>
	<"Sonda_V.V" #0000ff 0 3 1 0 0>
  </Tab>
</Diagrams>
<Paintings>
</Paintings>
