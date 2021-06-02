import React, { useState } from "react";
import { Button, Container, Grid } from "semantic-ui-react";
import DataProvider from "../../data/DataProvider";
import { connect } from "react-redux";
import Bar from "../../charts/Bar";
import DataConsumer from "../../data/DataConsumer";
import { buildBarOptions, buildDivergingOptions, buildPieOptions, buildTopsData } from './chartOptionsBuilder'
import './charts.scss'
import HalfPie from "../../charts/HalfPie";
import TheContent from "../../wp/template-parts/TheContent";
import Top from "../../charts/Top";
import DonorScoreCard from "../../charts/donorScorecard/DonorScoreCard";
import TopList from "../../charts/TopList/TopList";
import LoginWidget from "../../charts/login/LoginWidget";

const BarChar = (props) => {
  const { data, legends, colors, height, groupMode } = props
  const options = buildTopsData(data, true)
  return <Bar groupMode={groupMode} height={height} legends={legends} colors={colors} options={options}
              format={{ style: "percent", currency: "EUR" }}></Bar>
}
const TopChart = (props) => {
  const { data, legends, colors, height, groupMode } = props
  const options = buildTopsData(data)
  return <Top groupMode={groupMode} height={height} legends={legends} colors={colors} options={options}
              format={{ style: "percent", currency: "EUR" }}></Top>
}

const PieChart = (props) => {
  const { data, legends, colors, height } = props
  const options = buildPieOptions(data, true)
  return <HalfPie height={height} legends={legends} colors={colors} options={options}
                  format={{ style: "percent", currency: "EUR" }}></HalfPie>
}

const DonorScoreCardChart = (props) => {
  return <DonorScoreCard />;
}

const TopListsChart = (props) => {
  return <TopList />;
}

const LoginWidgetComponent = (props) => {
  return <LoginWidget />;
}
const Diverging = (props) => {
  const { data, legends, colors, height } = props
  const options = buildDivergingOptions(data, true)
  return <Diverging height={height} legends={legends} colors={colors} options={options}
                    format={{ style: "percent", currency: "EUR" }}></Diverging>
}


const Chart = (props) => {
  const { filters } = props
  console.log(props);
  const {
    editing = false,
    childContent,
    "data-height": height = 500,
    "data-chart-type": type = 'bar',
    'data-source': source = 'DG/5',
    'data-legends-left': left = 'Left Legend',
    'data-legends-bottom': title = 'chartTitle',
    'data-color-scheme': scheme = 'nivo',
    'data-color-by': colorBy = 'index',
    'data-group-mode': groupMode = 'stacked',
    'data-dualmode': dualMode,
    'data-chart-source-label': dataSourceLabel = "Source",
    'data-chart-data-source': dataSource = "NDIS",
    'data-toggle-info-label': toggleInfoLabel = "Info Graphic",
    'data-toggle-chart-label': toggleChartLabel = "Chart",
  } = props;
  let newSource = source;
  const [mode, setMode] = useState(editing ? "chart" : 'info')

  const legends = {
    title,
    left
  }
  const colors = {
    scheme: scheme,
    colorBy: colorBy
  }
  let child = null
  if (type === 'bar') {
    child = <BarChar height={`${height}px`} legends={legends} colors={colors} groupMode={groupMode}></BarChar>
  }
  if (type == 'halfPie') {
    child = <PieChart height={`${height}px`} legends={legends} colors={colors} groupMode={groupMode}></PieChart>
  }
  if (type == 'diverging1') {
    child = <h1>Soon</h1>
  }

  if (type === 'donorScorecard') {
    child = <DonorScoreCardChart />;
    newSource = 'DG/5';
  }
  if (type === 'topLists') {
    newSource = 'DG/5';
    child = <TopListsChart />;
  }

  if (type === 'loginWidget') {
    newSource = 'DG/5';
    child = <LoginWidgetComponent />;
  }


  if (type === 'TopChart') {
    child = <TopChart height={`${height}px`} legends={legends} colors={colors} groupMode={groupMode}></TopChart>
  }
  const dual = (dualMode === 'true')
  return <Container className={"chart container"} fluid={true}>

    <DataProvider store={newSource.split("/")} source={newSource}>

      {(!dual || mode == 'chart') && <Container className={"body"} fluid={true}><DataConsumer>
        {child}
      </DataConsumer></Container>}

    </DataProvider>

    {dual && childContent && mode == 'info' && <Container className={"body"}>
      <TheContent post={{ content: { rendered: childContent } }}></TheContent>
    </Container>}

    {!editing && dual && <Grid className={"footnote"}>
      <Grid.Column width={1}></Grid.Column>
      <Grid.Column width={7}>
        <Button className={(mode === 'info') ? "active" : ""}
                onClick={e => setMode('info')}>{toggleInfoLabel}</Button> |
        <Button className={(mode === 'chart') ? "active" : ""}
                onClick={e => setMode('chart')}>{toggleChartLabel}</Button>
      </Grid.Column>
      <Grid.Column textAlign={"right"} width={7}>
        <p>{dataSourceLabel} : {dataSource}</p>
      </Grid.Column>
      <Grid.Column width={1}></Grid.Column>
    </Grid>}
  </Container>
}


const mapStateToProps = (state, ownProps) => {
  return {}
}

const mapActionCreators = {};

export default connect(mapStateToProps, mapActionCreators)(Chart)