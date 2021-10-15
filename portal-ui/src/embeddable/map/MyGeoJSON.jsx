import React, { useRef, useEffect } from "react";
import { GeoJSON, useMap, useMapEvents } from "react-leaflet";
import { renderToStaticMarkup } from "react-dom/server";
import * as L from "leaflet";
import hash from 'object-hash';

const MyGeoJSON = (props) => {
  const layerRef = useRef(null);
  const { data, ...otherProps } = props;
  const addData = (layer, jsonData) => {
    layer.addData(jsonData);
  }
  const pointToLayer = (feature, latlng) => {
    const myIcon = L.divIcon({
      className: 'map-adm-icon',
      html: renderToStaticMarkup(<Bubble feature={feature} zoomLevel={map.getZoom()} />),
      iconSize: [60, 50]
    });
    return L.marker(latlng, { icon: myIcon });
  };

  useEffect(() => {
    const layer = layerRef.current;
    addData(layer, props.data);
  }, [props.data]);

  const map = useMapEvents({
    zoomend: () => {
      layerRef.current.clearLayers().addData(data);
    }
  });

  return (
    <GeoJSON key={hash(data)} ref={layerRef} {...otherProps} pointToLayer={pointToLayer} />
  );
}
const Bubble = ({ feature, zoomLevel }) => {

    return (<>
      <div
        className={`map-circle ${zoomLevel >= 9 || feature.properties.activityid.length > 999
          ? 'large' : 'medium'}`}>{feature.properties.activityid.length}</div>
      {zoomLevel >= 9 && (<div className="map-circle-label">{feature.properties.admName}</div>)}
    </>)
  }
;
export default MyGeoJSON;
