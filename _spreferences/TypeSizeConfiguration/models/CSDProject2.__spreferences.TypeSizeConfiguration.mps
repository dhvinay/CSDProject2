<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:80ccb311-f5c9-4ad5-8971-c575af96012c(CSDProject2.__spreferences.TypeSizeConfiguration)">
  <persistence version="9" />
  <languages>
    <use id="61c69711-ed61-4850-81d9-7714ff227fb0" name="com.mbeddr.core.expressions" version="5" />
  </languages>
  <imports />
  <registry>
    <language id="61c69711-ed61-4850-81d9-7714ff227fb0" name="com.mbeddr.core.expressions">
      <concept id="8463282783691618456" name="com.mbeddr.core.expressions.structure.UnsignedInt64tType" flags="ng" index="26Vqp1" />
      <concept id="8463282783691618461" name="com.mbeddr.core.expressions.structure.UnsignedInt8tType" flags="ng" index="26Vqp4" />
      <concept id="8463282783691618450" name="com.mbeddr.core.expressions.structure.UnsignedInt32tType" flags="ng" index="26Vqpb" />
      <concept id="8463282783691618440" name="com.mbeddr.core.expressions.structure.Int32tType" flags="ng" index="26Vqph" />
      <concept id="8463282783691618445" name="com.mbeddr.core.expressions.structure.Int64tType" flags="ng" index="26Vqpk" />
      <concept id="8463282783691618435" name="com.mbeddr.core.expressions.structure.Int16tType" flags="ng" index="26Vqpq" />
      <concept id="8463282783691618466" name="com.mbeddr.core.expressions.structure.UnsignedInt16tType" flags="ng" index="26VqpV" />
      <concept id="8463282783691618471" name="com.mbeddr.core.expressions.structure.UnsignedLongLongType" flags="ng" index="26VqpY" />
      <concept id="8463282783691618426" name="com.mbeddr.core.expressions.structure.Int8tType" flags="ng" index="26Vqqz" />
      <concept id="8463282783691596316" name="com.mbeddr.core.expressions.structure.LongLongType" flags="ng" index="26VBN5" />
      <concept id="8463282783691596310" name="com.mbeddr.core.expressions.structure.UnsignedLongType" flags="ng" index="26VBNf" />
      <concept id="8463282783691492730" name="com.mbeddr.core.expressions.structure.UnsignedIntType" flags="ng" index="26VXez" />
      <concept id="8463282783691492716" name="com.mbeddr.core.expressions.structure.UnsignedCharType" flags="ng" index="26VXeP" />
      <concept id="8864856114140038681" name="com.mbeddr.core.expressions.structure.DoubleType" flags="ng" index="2fgwQN" />
      <concept id="9149785691755093694" name="com.mbeddr.core.expressions.structure.IEEE754TypeSizeSpecification" flags="ng" index="2mYgW_">
        <property id="9149785691755093695" name="exists" index="2mYgW$" />
        <child id="9149785691755093698" name="ieee754Type" index="2mYgXp" />
        <child id="9149785691755093697" name="basicType" index="2mYgXq" />
      </concept>
      <concept id="9149785691754701072" name="com.mbeddr.core.expressions.structure.LongDoubleType" flags="ng" index="2p1N2b" />
      <concept id="595416243537320771" name="com.mbeddr.core.expressions.structure.UnsignedShortType" flags="ng" index="LMkMC" />
      <concept id="3335993110369949928" name="com.mbeddr.core.expressions.structure.ShortType" flags="ng" index="MySNB" />
      <concept id="3335993110369795381" name="com.mbeddr.core.expressions.structure.TypeSizeSpecification" flags="ng" index="MXy$U">
        <property id="3335993110370236888" name="exists" index="MzQRn" />
        <child id="7496733358578231499" name="c99Type" index="15Utue" />
        <child id="7496733358578231498" name="basicType" index="15Utuf" />
      </concept>
      <concept id="3335993110369795380" name="com.mbeddr.core.expressions.structure.TypeSizeConfiguration" flags="ng" index="MXy$V">
        <child id="9149785691755067704" name="ieee754Specifications" index="2mYqyz" />
        <child id="3869525881267655660" name="ssizeTType" index="2B$ca_" />
        <child id="3335993110369805710" name="specifications" index="MXv61" />
        <child id="8863019357864392147" name="sizeTType" index="2O5j3Q" />
        <child id="3813668170744198630" name="pointerDiffType" index="3kxMGo" />
        <child id="7808382574383152989" name="intPtrType" index="3sasR9" />
        <child id="7808382574383153001" name="uintPtrType" index="3sasRX" />
        <child id="5598157691785092886" name="vaList" index="3EM3Bk" />
        <child id="6658270785788810330" name="minFloatValue" index="3LaRDq" />
        <child id="6658270785788810339" name="maxDoubleValue" index="3LaRDz" />
        <child id="6658270785788810349" name="minDoubleValue" index="3LaRDH" />
        <child id="6658270785788810029" name="maxFloatValue" index="3LaROH" />
      </concept>
      <concept id="3390250080473522603" name="com.mbeddr.core.expressions.structure.SignedCharType" flags="ng" index="1dkrvn" />
      <concept id="4739982148980385695" name="com.mbeddr.core.expressions.structure.FloatType" flags="ng" index="3AreGT" />
      <concept id="8860443239512128108" name="com.mbeddr.core.expressions.structure.IntType" flags="ng" index="3TlMh2" />
      <concept id="1670233242589902798" name="com.mbeddr.core.expressions.structure.ScientificNumber" flags="ng" index="3VGQI6">
        <property id="1670233242589904217" name="prefix" index="3VGQ4h" />
        <property id="1670233242589904219" name="postfix" index="3VGQ4j" />
      </concept>
      <concept id="86532984527104137" name="com.mbeddr.core.expressions.structure.LongType" flags="ng" index="1X9cn3" />
    </language>
  </registry>
  <node concept="MXy$V" id="1ItImwDchWF">
    <node concept="26Vqpb" id="1ItImwDchXu" role="3kxMGo" />
    <node concept="1X9cn3" id="1ItImwDchXv" role="3sasR9" />
    <node concept="26VBNf" id="1ItImwDchXw" role="3sasRX" />
    <node concept="26Vqpb" id="1ItImwDchXx" role="2O5j3Q" />
    <node concept="26Vqph" id="1ItImwDchXy" role="2B$ca_" />
    <node concept="26Vqpb" id="1ItImwDchXz" role="3EM3Bk" />
    <node concept="3VGQI6" id="1ItImwDchX_" role="3LaRDq">
      <property role="3VGQ4h" value="-1" />
      <property role="3VGQ4j" value="37" />
    </node>
    <node concept="3VGQI6" id="1ItImwDchXA" role="3LaRDH">
      <property role="3VGQ4h" value="-1" />
      <property role="3VGQ4j" value="37" />
    </node>
    <node concept="3VGQI6" id="1ItImwDchXB" role="3LaROH">
      <property role="3VGQ4h" value="1" />
      <property role="3VGQ4j" value="37" />
    </node>
    <node concept="3VGQI6" id="1ItImwDchXC" role="3LaRDz">
      <property role="3VGQ4h" value="1" />
      <property role="3VGQ4j" value="37" />
    </node>
    <node concept="MXy$U" id="1ItImwDchXF" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="1dkrvn" id="1ItImwDchXD" role="15Utuf" />
      <node concept="26Vqqz" id="1ItImwDchXE" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchXI" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="MySNB" id="1ItImwDchXG" role="15Utuf" />
      <node concept="26Vqpq" id="1ItImwDchXH" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchXL" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="3TlMh2" id="1ItImwDchXJ" role="15Utuf" />
      <node concept="26Vqph" id="1ItImwDchXK" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchXO" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="1X9cn3" id="1ItImwDchXM" role="15Utuf" />
      <node concept="26Vqpk" id="1ItImwDchXN" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchXR" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="26VBN5" id="1ItImwDchXP" role="15Utuf" />
      <node concept="26Vqpk" id="1ItImwDchXQ" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchXU" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="26VXeP" id="1ItImwDchXS" role="15Utuf" />
      <node concept="26Vqp4" id="1ItImwDchXT" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchXX" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="LMkMC" id="1ItImwDchXV" role="15Utuf" />
      <node concept="26VqpV" id="1ItImwDchXW" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchY0" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="26VXez" id="1ItImwDchXY" role="15Utuf" />
      <node concept="26Vqpb" id="1ItImwDchXZ" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchY3" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="26VBNf" id="1ItImwDchY1" role="15Utuf" />
      <node concept="26Vqp1" id="1ItImwDchY2" role="15Utue" />
    </node>
    <node concept="MXy$U" id="1ItImwDchY6" role="MXv61">
      <property role="MzQRn" value="true" />
      <node concept="26VqpY" id="1ItImwDchY4" role="15Utuf" />
      <node concept="26Vqp1" id="1ItImwDchY5" role="15Utue" />
    </node>
    <node concept="2mYgW_" id="1ItImwDchY9" role="2mYqyz">
      <property role="2mYgW$" value="true" />
      <node concept="3AreGT" id="1ItImwDchY7" role="2mYgXq" />
      <node concept="3AreGT" id="1ItImwDchY8" role="2mYgXp" />
    </node>
    <node concept="2mYgW_" id="1ItImwDchYc" role="2mYqyz">
      <property role="2mYgW$" value="true" />
      <node concept="2fgwQN" id="1ItImwDchYa" role="2mYgXq" />
      <node concept="2fgwQN" id="1ItImwDchYb" role="2mYgXp" />
    </node>
    <node concept="2mYgW_" id="1ItImwDchYf" role="2mYqyz">
      <property role="2mYgW$" value="true" />
      <node concept="2p1N2b" id="1ItImwDchYd" role="2mYgXq" />
      <node concept="2p1N2b" id="1ItImwDchYe" role="2mYgXp" />
    </node>
  </node>
</model>

