<GameFile>
  <PropertyGroup Name="Caracter" Type="Node" ID="74575a49-892a-499e-99ff-873df60c7cb1" Version="2.3.3.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="5" Speed="0.5000" ActivedAnimationName="default">
        <Timeline ActionTag="-1943063023" Property="VisibleForFrame">
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-1943063023" Property="FileData">
          <TextureFrame FrameIndex="1" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="2" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character2.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character3.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="4" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character2.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="5" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character1.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="-1943063023" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="1" Tween="False" Src="770" Dst="771" />
          <BlendFuncFrame FrameIndex="2" Tween="False" Src="770" Dst="771" />
          <BlendFuncFrame FrameIndex="3" Tween="False" Src="770" Dst="771" />
          <BlendFuncFrame FrameIndex="4" Tween="False" Src="770" Dst="771" />
          <BlendFuncFrame FrameIndex="5" Tween="False" Src="770" Dst="771" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="default" StartIndex="0" EndIndex="0">
          <RenderColor A="150" R="255" G="0" B="255" />
        </AnimationInfo>
        <AnimationInfo Name="chop" StartIndex="1" EndIndex="6">
          <RenderColor A="150" R="255" G="165" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" CustomClassName="Character" Tag="4" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Cat" ActionTag="-1943063023" Tag="5" IconVisible="False" LeftMargin="-365.0000" TopMargin="-217.0000" ctype="SpriteObjectData">
            <Size X="365.0000" Y="217.0000" />
            <AnchorPoint ScaleX="1.0000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Assets/Images/resources-2x/character1.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>