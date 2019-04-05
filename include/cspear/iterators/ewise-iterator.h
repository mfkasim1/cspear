#ifndef CSPEAR_ITERATORS_EWISE_ITERATOR_H
#define CSPEAR_ITERATORS_EWISE_ITERATOR_H

#include <vector>
#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>
#include <cspear/views/slice-view.h>

namespace csp {
  template <typename T, typename I, typename View>
  class EWiseIterator {
    public:
    // constructor
    EWiseIterator(T* data, const View& view);

    // iterator operator
    T& operator*();
    EWiseIterator& operator++();
    operator bool() const;
  };

  // partial template specialization for different views
  template <typename T, typename I>
  class EWiseIterator<T,I,ContiguousView<I> > {
    I sz_ = 0;
    T* data_ = NULL;
    I offset_ = 0;

    public:
    // constructor
    EWiseIterator(T* data, const ContiguousView<I>& view) {
      sz_ = view.size();
      data_ = data;
      offset_ = 0;
    }

    // iterator operator
    inline T& operator*() {
      return *data_;
    }

    inline EWiseIterator& operator++() {
      data_++;
      offset_++;
      return *this;
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };

  template <typename T, typename I>
  class EWiseIterator<T,I,FilterView<I> > {
    I sz_ = 0;
    T* data_ = NULL;
    T* origin_data_ = NULL;
    I offset_ = 0;
    const I* all_idxs_ = NULL;
    const I* idxs_ = NULL;

    public:
    EWiseIterator(T* data, const FilterView<I>& view) {
      sz_ = view.size();
      origin_data_ = data;
      offset_ = 0;
      idxs_ = view.idxs();
      all_idxs_ = idxs_;
      if (sz_ == 0)
        data_ = NULL;
      else
        data_ = &origin_data_[*idxs_];
    }

    // iterator operator
    inline T& operator*() {
      return origin_data_[*idxs_];
    }

    inline EWiseIterator& operator++() {
      idxs_++;
      offset_++;
      return *this;
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };

  template <typename T, typename I>
  class EWiseIterator<T,I,SliceView<I> > {
    T* it_ = NULL;
    I remaining_ = 0;
    std::vector<I> orig_nsteps_;
    std::vector<I> nsteps_;
    std::vector<I> skips_;
    std::vector<I> strides_;
    std::vector<I> shapes_;

    void _set_up_nsteps_and_skips(const std::vector< Slice<I> >& slices,
                                 const std::vector<I>& dshape) {
      I nsize = slices.size() - 1;
      orig_nsteps_.resize(nsize);
      skips_.resize(nsize);
      strides_.resize(nsize);
      shapes_.resize(nsize);
      auto itslice = slices.rbegin();
      auto itshape = dshape.rbegin();
      I skip_stride = 1;
      for (I i = 0; i < nsize; ++i, ++itslice, ++itshape) {
        auto& slice = *itslice;
        auto& shape = *itshape;
        orig_nsteps_[i] = slice.nelmt;
        skips_[i] = (shape - (slice.end - slice.begin)) * skip_stride;
        strides_[i] = slice.step;
        shapes_[i] = skip_stride;
        skip_stride *= shape;
      }
      nsteps_ = orig_nsteps_;
    }

    I _get_step() {
      I idx = 0;
      I step = 1;
      I sz = nsteps_.size();
      for (auto& nstep : nsteps_) {
        --nstep;
        if (nstep == 0) {
          step += skips_[idx];
          nstep = orig_nsteps_[idx];
          ++idx;
          continue;
        }
        step += (strides_[idx]-1) * shapes_[idx];
        break;
      }
      return step;
    }

  public:
    // constructor
    EWiseIterator(T* data, const SliceView<I>& view) {
      it_ = data;
      remaining_ = view.size();
      _set_up_nsteps_and_skips(view.slices(), view.data_shape());
    }

    // iterator operator
    T& operator*() {
      return *it_;
    }

    EWiseIterator& operator++() {
      // get the step size
      I step = _get_step();

      // move the iterator
      it_ += step;

      --remaining_;
      return *this;
    }

    operator bool() const {
      return remaining_ > 0;
    }
  };
}

#endif
