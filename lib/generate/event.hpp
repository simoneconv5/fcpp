// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file event.hpp
 * @brief Collection of generators of events. Contrary to random distributions, events generators are stateful, that is, the generation of the next event depend on the previous events generated (and are generated in increasing order).
 */

#ifndef FCPP_GENERATE_EVENT_H_
#define FCPP_GENERATE_EVENT_H_

#include <algorithm>
#include <array>
#include <limits>
#include <type_traits>

#include "lib/settings.hpp"
#include "lib/common/traits.hpp"
#include "lib/generate/distribution.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {


//! @brief Empty generator for no events.
struct event_never {
    //! @brief The type of results generated.
    using type = times_t;
    
    //! @brief Default constructor.
    event_never() = default;
    
    //! @brief Returns next event to schedule.
    template <typename G>
    times_t operator()(G&) {
        return std::numeric_limits<times_t>::max(); // no event to schedule
    }
};


/**
 * @brief Generator of a series of contemporary events.
 * @param T Distribution generating the time of the events.
 * @param n Number of events.
 * @param same Whether the same event should be produced (defaults to true).
 */
//{@
//! @brief General form.
template <typename T, size_t n, bool same = true>
class event_multiple;
//! @brief Case for identical events.
template <typename T, size_t n>
class event_multiple<T, n, true> {
    static_assert(std::is_same<typename T::type, times_t>::value, "the distribution T must generate a times_t value");
    
    //! @brief The type of results generated.
    using type = times_t;
    
    // The time of the events.
    times_t t;
    // Number of calls to next so far.
    size_t i = 0;
    
  public:
    //! @brief Default constructor.
    event_multiple() = default;
    
    //! @brief Returns next event to schedule.
    template <typename G>
    times_t operator()(G& g) {
        if (i==0) {
            T distr;
            t = distr(g);
        }
        return (++i <= n) ? t : std::numeric_limits<times_t>::max();
    }
};
//! @brief Case for possibly different events.
template <typename T, size_t n>
class event_multiple<T, n, false> {
    static_assert(std::is_same<typename T::type, times_t>::value, "the distribution T must generate a times_t value");
    
    //! @brief The type of results generated.
    using type = times_t;
    
    // The time of the events.
    std::array<times_t, n> pending;
    // Number of calls to next so far.
    size_t i = 0;
    
  public:
    //! @brief Default constructor.
    event_multiple() = default;
    
    //! @brief Returns next event to schedule.
    template <typename G>
    times_t operator()(G& g) {
        if (i==0) {
            T distr;
            for (size_t j=0; j<n; ++j) pending[j] = distr(g);
            std::sort(pending.begin(), pending.end());
        }
        return (++i <= n) ? pending[i-1] : std::numeric_limits<times_t>::max();
    }
};
//@}


/**
 * @brief Generator of a series of events at given times.
 * @param T Distributions generating the time of the events.
 */
template <typename... T>
class event_sequence {
    static_assert(all_true<std::is_same<typename T::type, times_t>::value...>, "the distributions T must generate a times_t value");
    
    //! @brief The type of results generated.
    using type = times_t;
    
    // List of events to come.
    std::array<times_t, sizeof...(T)> pending;
    // Number of calls to next so far.
    size_t i = 0;
    
  public:
    //! @brief Default constructor.
    event_sequence() = default;
    
    //! @brief Returns next event to schedule.
    template <typename G>
    times_t operator()(G& g) {
        if (i == 0) {
            pending = std::array<times_t, sizeof...(T)>({details::call_distr<T>(g)...});
            std::sort(pending.begin(), pending.end());
        }
        return (++i <= sizeof...(T)) ? pending[i-1] : std::numeric_limits<times_t>::max();
    }
};


/**
 * @brief Generator of a series of events at given times.
 * The sooner terminating condition between E and N is selected.
 * @param S Distribution for the first event.
 * @param P Distribution regulating the period.
 * @param E Distribution for the last event.
 * @param N Distribution for the number of events to be generated.
 */
template <typename S, typename P = S, typename E = event_never, typename N = constant_distribution<size_t, std::numeric_limits<size_t>::max()>>
class event_periodic {
    static_assert(std::is_same<typename S::type, times_t>::value, "the distribution S must generate a times_t value");
    static_assert(std::is_same<typename P::type, times_t>::value, "the distribution P must generate a times_t value");
    static_assert(std::is_same<typename E::type, times_t>::value, "the distribution E must generate a times_t value");
    static_assert(std::is_same<typename N::type, size_t>::value, "the distribution N must generate a size_t value");
    
    //! @brief The type of results generated.
    using type = times_t;
    
    // Period distribution;
    P dp;
    // Last event happened and terminal time.
    times_t t, te;
    // Number of calls to next so far.
    size_t i = 0, n;

  public:
    //! @brief Default constructor.
    event_periodic() = default;
    
    //! @brief Returns next event to schedule.
    template <typename G>
    times_t operator()(G& g) {
        if (i == 0) {
            N dn;
            n = dn(g);
            E de;
            te = de(g);
            S ds;
            t = ds(g);
        } else t += dp(g);
        return (++i <= n and t < te) ? t : std::numeric_limits<times_t>::max();
    }
};


}

#endif // FCPP_GENERATE_EVENT_H_
