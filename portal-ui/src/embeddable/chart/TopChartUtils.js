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