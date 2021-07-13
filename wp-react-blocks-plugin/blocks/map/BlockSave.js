/* eslint-disable react/react-in-jsx-scope */
import { useBlockProps } from '@wordpress/block-editor';
import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
const SaveComponent = (props) => {
  const {
    toggleSelection, setAttributes, attributes: {
      height,
      baseMap,
      adminLevel,
      viewMoreLink,
      viewMorePosition,
      zoomLevel,
      zoomTextIn,
      zoomTextOut,
      centerText,
      resetText
    }
  } = props;
  const blockProps = useBlockProps.save({
    className: 'tcdi component chart'
  });


  return (
    <div className={"tcdi-component"}
         data-component={"map"}
         data-height={height}
         data-base-map={baseMap}
         data-admin-level={adminLevel}
         data-view-more-link={viewMoreLink}
         data-view-more-position={viewMorePosition}
         data-zoom-level={zoomLevel}
         data-zoom-title-out={zoomTextOut}
         data-zoom-title-in={zoomTextIn}
         data-center-text={centerText}
         data-reset-text={resetText}
    >
      <InnerBlocks.Content />
    </div>


  );
}


export default SaveComponent