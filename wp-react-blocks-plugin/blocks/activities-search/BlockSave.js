/* eslint-disable react/react-in-jsx-scope */
import { useBlockProps } from '@wordpress/block-editor';
import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
const SaveComponent = (props) => {
  const {
    toggleSelection, setAttributes, attributes: {
      height,
      searchTitle,
      searchTooltip,
      searchDescription,
      searchHint,
      searchButton,
      searchExtendedSlug,
      searchType
    }
  } = props;
  const blockProps = useBlockProps.save({
    className: 'tcdi component chart'
  });


  return (
    <div className={"tcdi-component"}
         data-component={"activitiesSearch"}
         data-height={height}
         data-search-title={searchTitle}
         data-search-description={searchDescription}
         data-search-hint={searchHint}
         data-search-tooltip={searchTooltip}
         data-search-button={searchButton}
         data-search-extended-slug={searchExtendedSlug}
         data-search-type={searchType}

    >
      <InnerBlocks.Content />
    </div>


  );
}


export default SaveComponent