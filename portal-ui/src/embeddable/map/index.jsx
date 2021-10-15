import React from 'react';
import MapComponent from "./MapComponent";
import DataProvider from "../data/DataProvider";
import { Container } from "semantic-ui-react";
import DataConsumer from "../data/DataConsumer";
import { ADMIN_LEVEL_ID_TO_VALUE } from "./MapConstants";

const Map = (props) => {
  const {
    'data-height': height = 500,
    'data-base-map': baseMap = 'openStreetMaps',
    'data-admin-level': adminLevel = 'adm-0',
    'data-zoom-title-in': zoomTitleIn = 'Zoom In',
    'data-zoom-title-out': zoomTitleOut = 'Zoom Out',
    'data-zoom-level': zoomLevel = 8,
    'data-view-more-position': viewMorePosition = 'bottomleft',
    'data-view-more-text': viewMoreText = 'View more',
    'data-view-more-link': viewMoreLink = "https://www.developmentgateway.org",
    'data-center-text': centerText = 'Center',
    'data-reset-text': resetText = 'Reset'

  }
    = props;
  const adminLevelParam = ADMIN_LEVEL_ID_TO_VALUE.find(a => a.id === adminLevel).value;
  const viewMore = { link: viewMoreLink, position: viewMorePosition, text: viewMoreText };
  const zoom = { level: zoomLevel, titleIn: zoomTitleIn, titleOut: zoomTitleOut };
  const labels = { reset: resetText, center: centerText };
  const child = (<MapComponent
    height={height} baseMap={baseMap} viewMore={viewMore} zoom={zoom} labels={labels}
  />);


  return <DataProvider source={adminLevelParam} app={'map'} store={'map'}>
    <Container style={{ "height": `${height}px` }} className={"body"} fluid={true}><DataConsumer>
      {child}
    </DataConsumer></Container>

  </DataProvider>
};
export default Map;