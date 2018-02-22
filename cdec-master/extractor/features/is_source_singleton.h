#ifndef _IS_SOURCE_SINGLETON_H_
#define _IS_SOURCE_SINGLETON_H_

#include "feature.h"

namespace extractor {
namespace features {

/**
 * Boolean feature checking if the source phrase occurs only once in the data.
 */
class IsSourceSingleton : public Feature {
 public:
  double Score(const FeatureContext& context) const;

  string GetName() const;
};

} // namespace features
} // namespace extractor

#endif
