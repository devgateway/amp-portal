/* eslint-disable react/react-in-jsx-scope */
import { useBlockProps } from '@wordpress/block-editor';
import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
const SaveComponent = (props) => {
  const {
    toggleSelection, setAttributes, attributes: {
      height,
      topType,
      topSize,
      topTitle,
      topDescription,
      topMonth
    }
  } = props;
  const blockProps = useBlockProps.save({
    className: 'tcdi component chart'
  });


  return (
    <div className={"tcdi-component"}
         data-component={"topLists"}
         data-height={height}
         data-top-type={topType}
         data-top-size={topSize}
         data-top-title={topTitle}
         data-top-description={topDescription}
         data-top-month={topMonth}
    >
      <InnerBlocks.Content />
    </div>


  );
}


export default SaveComponent