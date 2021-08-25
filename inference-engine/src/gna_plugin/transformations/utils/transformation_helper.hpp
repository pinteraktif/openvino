// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

namespace GNAPluginNS {

struct ConvData {
    size_t input_height;
    size_t input_width;
    size_t input_channel_count;
    size_t filter_height;
    size_t filter_width;
    size_t filter_count;
    size_t filter_channel_count;
    size_t filter_dilation_height;
    size_t filter_dilation_width;
    size_t filter_stride_height;
    size_t filter_stride_width;
    size_t output_height;
    size_t output_width;
    size_t output_channel_count;
    size_t pads_begin_width;
    size_t pads_begin_height;
    size_t pads_end_width;
    size_t pads_end_height;
    ngraph::op::PadType padding_type;
    ngraph::element::Type element_type;
};

/**
 * @brief gets all convolution related data into a struct for further processing
 * @param conv convolution node to get data of
 * @param conv_data convolution data structure to put data into
 * @return void
 */
void GetConvData(std::shared_ptr<ngraph::opset7::Convolution> conv, ConvData& conv_data);

/**
 * @brief ngraph matcher predicate fusing existing predicates for consumers count and rank of a layer
 * @param expected_count expected consumers count for of node
 * @param expected_rank expected node rank
 * @return predicate function wrapper
 */
std::function<bool(ngraph::Output<ngraph::Node>)> consumers_and_rank(const size_t expected_count, const ngraph::Dimension& expected_rank);

/**
 * @brief checks whether transpose matches a given order
 * @param transpose transpose layer
 * @param order order of transposition to be compared with
 * @return true if the order matches, false otherwise
 */
bool TransposeOrderMatches(std::shared_ptr<ngraph::opset7::Transpose> transpose, std::vector<size_t> order);

/**
 * @brief performs a crop of a flattened input tensor
 * @param input input layer
 * @param offset offset to start the crop at* 
 * @param size size of the crop
 * @return pointer to the newly created slice
 */
std::shared_ptr<ngraph::opset7::StridedSlice> FlatCrop(ngraph::Output<ngraph::Node> input, size_t offset, size_t size);
} // namespace GNAPluginNS