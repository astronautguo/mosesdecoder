/*
 * FeatureFunction.h
 *
 *  Created on: 23 Oct 2015
 *      Author: hieu
 */

#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include "../TypeDef.h"
#include "../Phrase.h"

namespace Moses2
{
template<typename WORD>
class TargetPhrase;

class System;
class PhraseImpl;
class TargetPhrases;
class Scores;
class ManagerBase;
class MemPool;

namespace SCFG
{
class TargetPhrase;
class TargetPhrases;
class Word;
}

class FeatureFunction
{
public:

  FeatureFunction(size_t startInd, const std::string &line);
  virtual ~FeatureFunction();
  virtual void Load(System &system)
  {
  }

  size_t GetStartInd() const
  {
    return m_startInd;
  }
  size_t GetNumScores() const
  {
    return m_numScores;
  }
  const std::string &GetName() const
  {
    return m_name;
  }
  void SetName(const std::string &val)
  {
    m_name = val;
  }

  virtual size_t HasPhraseTableInd() const
  {
    return false;
  }
  void SetPhraseTableInd(size_t ind)
  {
    m_PhraseTableInd = ind;
  }
  size_t GetPhraseTableInd() const
  {
    return m_PhraseTableInd;
  }

  // may have more factors than actually need, but not guaranteed.
  // For SCFG decoding, the source contains non-terminals, NOT the raw
  // source from the input sentence
  virtual void
  EvaluateInIsolation(MemPool &pool, const System &system, const Phrase<Moses2::Word> &source,
      const TargetPhrase<Moses2::Word> &targetPhrase, Scores &scores,
      SCORE *estimatedScore) const = 0;

  /*
   virtual void
   EvaluateInIsolation(MemPool &pool, const System &system,
   const Phrase &source, const SCFG::TargetPhrase &targetPhrase,
   Scores &scores,
   SCORE *estimatedScore) const {}
   */

  virtual void EvaluateAfterTablePruning(MemPool &pool,
      const TargetPhrases &tps, const Phrase<Moses2::Word> &sourcePhrase) const
  {
  }

  virtual void EvaluateAfterTablePruning(MemPool &pool,
      const SCFG::TargetPhrases &tps, const Phrase<SCFG::Word> &sourcePhrase) const
  {
  }

  // clean up temporary memory, called after processing each sentence
  virtual void CleanUpAfterSentenceProcessing()
  {
  }

protected:
  size_t m_startInd;
  size_t m_numScores;
  size_t m_PhraseTableInd;
  std::string m_name;
  std::vector<std::vector<std::string> > m_args;
  bool m_tuneable;

  virtual void SetParameter(const std::string& key, const std::string& value);
  virtual void ReadParameters();
  void ParseLine(const std::string &line);
};

}

