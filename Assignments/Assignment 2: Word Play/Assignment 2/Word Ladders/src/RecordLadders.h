/*
 * Header: RecordLadders.h
 *
 * Exports the recordLadderBetween and recordNoLadderBetween functions,
 * which we'll use when we're grading your assignment submission.
 */

#ifndef RecordLadders_Included
#define RecordLadders_Included

#include <string>

/**
 * Records a ladder between two particular words.
 *
 * @param start  The starting word.
 * @param end    The ending word.
 * @param ladder The ladder you found.
 */
template <typename LadderType>
void recordLadderBetween(const std::string& start,
                         const std::string& end,
                         const LadderType&  ladder) {
    /* This function has no effect now, but we will use it during
     * grading! The lines below are there just to silence compiler
     * warnings about not using the parameters.
     */
    (void)start;
    (void)end;
    (void)ladder;
}

/**
 * Records that there is no ladder between two given words.
 *
 * @param start  The starting word.
 * @param end    The ending word.
 */
inline void recordNoLadderBetween(const std::string& start,
                                  const std::string& end) {
    /* This function has no effect now, but we will use it during
     * grading! The lines below are there just to silence compiler
     * warnings about not using the parameters.
     */
    (void)start;
    (void)end;
}

#endif
