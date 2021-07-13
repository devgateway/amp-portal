import React, { useRef } from "react";
import {
  MapContainer,
  useMap,
  ZoomControl
} from 'react-leaflet';
import 'leaflet/dist/leaflet.css';
import './map.scss';

import layers from './Utils/Layers';
import CenterIcon from './icons/centermap.png';
import ResetIcon from './icons/reset.svg';
import MyGeoJSON from "./MyGeoJSON";
import Control from "./Utils/Control";

const MapComponent = ({ height, baseMap, viewMore, zoom, data, labels }) => {

  const center = [18.99688107906594, -73.05741235613824];

  const geoJsonLayer = useRef(null);

  return (<MapContainer
    style={{ "height": height + "px" }}
    center={center}
    zoom={zoom.level}
    zoomControl={false}
    scrollWheelZoom={false}>
    {layers.get(baseMap)}
    <ZoomControl
      zoomInTitle={zoom.titleIn}
      zoomOutTitle={zoom.titleOut}
    />
    <Control position="topleft" className="leaflet-control-zoom leaflet-bar leaflet-control map-control">
      <CenterResetMap center={center} icon={CenterIcon} label={labels.center} />
      <CenterResetMap center={center} icon={ResetIcon} label={labels.reset} zoomLevel={zoom.level} />
    </Control>
    <MyGeoJSON data={data} ref={geoJsonLayer} />
    <Control position={viewMore.position} className="leaflet-control leaflet-bar">
      <div className="view-more"><a href={viewMore.link} target="_blank" rel='noreferrer'>View more</a></div>
    </Control>
  </MapContainer>);
}

const CenterResetMap = (props) => {
  const { center, icon, zoomLevel, label } = props;
  const map = useMap();
  const handleCenterClick = (event) => {
    const zoomTo = zoomLevel ? zoomLevel : map.getZoom();
    map.flyTo(center, zoomTo);
  }
  return (<a onClick={handleCenterClick}>
    <img
      src={icon}
      className="map-control"
      alt={label}
      title={label} />
  </a>)
}


export default MapComponent;