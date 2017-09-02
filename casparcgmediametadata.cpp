#include "casparcgmediametadata.h"

CasparCGMediaMetaData::CasparCGMediaMetaData() :
    CasparCGMetaData(), m_transitionDuration(1),
    m_triggerOnNext(false)
{
}

CasparCGMediaMetaData::CasparCGMediaMetaData(const CasparCGMediaMetaData &other) :
    CasparCGMetaData(other)
{
    m_transition = other.m_transition;
    m_transitionDuration = other.m_transitionDuration;
    m_tween = other.m_tween;
    m_direction = other.m_direction;
    m_triggerOnNext = other.m_triggerOnNext;
}
