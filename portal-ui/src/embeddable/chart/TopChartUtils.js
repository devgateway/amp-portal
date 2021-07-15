import { colorSchemes } from "@nivo/colors";

export const getColor = (item, colors, filter) => {
  if (filter && filter.includes(item.id)) {
    return '#EEE';
  }
  let color = colors.scheme === 'amp_dashboards' ? ampColors : colorSchemes[colors.scheme];
  const index = item.index !== undefined ? item.index :
    item.data !== undefined ? item.data.index : null;
  return color[index];
}
const ampColors = ['rgba(90, 153, 199, 1)',
  'rgba(195, 214, 238, 1)',
  'rgba(255, 160, 87, 1)',
  'rgba(255, 204, 154, 1)',
  'rgba(99, 184, 99, 1)',
  'rgba(153, 153, 153, 1)',
  'rgba(217, 91, 95, 1)',
  'rgba(253, 170, 170, 1)',
  'rgba(166, 133, 196, 1)',
  'rgba(206, 189, 218, 1)',
];

const shadeColor = (color, percent) => {

  let R = parseInt(color.substring(1, 3), 16);
  let G = parseInt(color.substring(3, 5), 16);
  let B = parseInt(color.substring(5, 7), 16);

  R = Math.round(R * (100 + percent) / 100);
  G = Math.round(G * (100 + percent) / 100);
  B = Math.round(B * (100 + percent) / 100);

  R = (R < 255) ? R : 255;
  G = (G < 255) ? G : 255;
  B = (B < 255) ? B : 255;

  let RR = ((R.toString(16).length === 1) ? "0" + R.toString(16) : R.toString(16));
  let GG = ((G.toString(16).length === 1) ? "0" + G.toString(16) : G.toString(16));
  let BB = ((B.toString(16).length === 1) ? "0" + B.toString(16) : B.toString(16));

  return "#" + RR + GG + BB;
}