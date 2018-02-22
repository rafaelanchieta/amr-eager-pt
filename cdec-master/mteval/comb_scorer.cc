#include "comb_scorer.h"

#include <cstdio>

using namespace std;

class BLEUTERCombinationScore : public ScoreBase<BLEUTERCombinationScore> {
  friend class BLEUTERCombinationScorer;
 public:
  ~BLEUTERCombinationScore();
  float ComputePartialScore() const { return 0.0;}
  float ComputeScore() const {
    return (bleu->ComputeScore() - ter->ComputeScore()) / 2.0f;
  }
  void ScoreDetails(string* details) const {
    char buf[160];
    sprintf(buf, "Combi = %.2f, BLEU = %.2f, TER = %.2f",
      ComputeScore()*100.0f, bleu->ComputeScore()*100.0f, ter->ComputeScore()*100.0f);
    *details = buf;
  }
  void PlusPartialEquals(const Score& rhs, int oracle_e_cover, int oracle_f_cover, int src_len){}

  void PlusEquals(const Score& delta, const float scale) {
    bleu->PlusEquals(*static_cast<const BLEUTERCombinationScore&>(delta).bleu, scale);
    ter->PlusEquals(*static_cast<const BLEUTERCombinationScore&>(delta).ter, scale);
  }
  void PlusEquals(const Score& delta) {
    bleu->PlusEquals(*static_cast<const BLEUTERCombinationScore&>(delta).bleu);
    ter->PlusEquals(*static_cast<const BLEUTERCombinationScore&>(delta).ter);
  }



  ScoreP GetOne() const {
    BLEUTERCombinationScore* res = new BLEUTERCombinationScore;
    res->bleu = bleu->GetOne();
    res->ter = ter->GetOne();
    return ScoreP(res);
  }
  ScoreP GetZero() const {
    BLEUTERCombinationScore* res = new BLEUTERCombinationScore;
    res->bleu = bleu->GetZero();
    res->ter = ter->GetZero();
    return ScoreP(res);
  }
  void Subtract(const Score& rhs, Score* res) const {
    bleu->Subtract(*static_cast<const BLEUTERCombinationScore&>(rhs).bleu,
                   static_cast<BLEUTERCombinationScore*>(res)->bleu.get());
    ter->Subtract(*static_cast<const BLEUTERCombinationScore&>(rhs).ter,
                  static_cast<BLEUTERCombinationScore*>(res)->ter.get());
  }
  void Encode(std::string* out) const {
    string bs, ts;
    bleu->Encode(&bs);
    ter->Encode(&ts);
    out->clear();
    (*out) += static_cast<char>(bs.size());
    (*out) += bs;
    (*out) += ts;
  }
  bool IsAdditiveIdentity() const {
    return bleu->IsAdditiveIdentity() && ter->IsAdditiveIdentity();
  }
 private:
  ScoreP bleu;
  ScoreP ter;
};

BLEUTERCombinationScore::~BLEUTERCombinationScore() {
}

BLEUTERCombinationScorer::BLEUTERCombinationScorer(const vector<vector<WordID> >& refs) {
  bleu_ = SentenceScorer::CreateSentenceScorer(IBM_BLEU, refs);
  ter_ = SentenceScorer::CreateSentenceScorer(TER, refs);
}

BLEUTERCombinationScorer::~BLEUTERCombinationScorer() {
}

ScoreP BLEUTERCombinationScorer::ScoreCCandidate(const vector<WordID>& hyp) const {
  return ScoreP();
}

ScoreP BLEUTERCombinationScorer::ScoreCandidate(const std::vector<WordID>& hyp) const {
  BLEUTERCombinationScore* res = new BLEUTERCombinationScore;
  res->bleu = bleu_->ScoreCandidate(hyp);
  res->ter = ter_->ScoreCandidate(hyp);
  return ScoreP(res);
}

ScoreP BLEUTERCombinationScorer::ScoreFromString(const std::string& in) {
  int bss = in[0];
  BLEUTERCombinationScore* r = new BLEUTERCombinationScore;
  r->bleu = SentenceScorer::CreateScoreFromString(IBM_BLEU, in.substr(1, bss));
  r->ter = SentenceScorer::CreateScoreFromString(TER, in.substr(1 + bss));
  return ScoreP(r);
}


class BLEUCBLEUCombinationScore : public ScoreBase<BLEUCBLEUCombinationScore> {
  friend class BLEUCBLEUCombinationScorer;
 public:
  ~BLEUCBLEUCombinationScore();
  float ComputePartialScore() const { return 0.0;}
  float ComputeScore() const {
    return (bleu->ComputeScore() + cbleu->ComputeScore()) / 2.0f;
  }
  void ScoreDetails(string* details) const {
    char buf[160];
    sprintf(buf, "Combi = %.2f, BLEU = %.2f, CBLEU = %.2f",
      ComputeScore()*100.0f, bleu->ComputeScore()*100.0f, cbleu->ComputeScore()*100.0f);
    *details = buf;
  }
  void PlusPartialEquals(const Score& rhs, int oracle_e_cover, int oracle_f_cover, int src_len){}

  void PlusEquals(const Score& delta, const float scale) {
    bleu->PlusEquals(*static_cast<const BLEUCBLEUCombinationScore&>(delta).bleu, scale);
    cbleu->PlusEquals(*static_cast<const BLEUCBLEUCombinationScore&>(delta).cbleu, scale);
  }
  void PlusEquals(const Score& delta) {
    bleu->PlusEquals(*static_cast<const BLEUCBLEUCombinationScore&>(delta).bleu);
    cbleu->PlusEquals(*static_cast<const BLEUCBLEUCombinationScore&>(delta).cbleu);
  }



  ScoreP GetOne() const {
    BLEUCBLEUCombinationScore* res = new BLEUCBLEUCombinationScore;
    res->bleu = bleu->GetOne();
    res->cbleu = cbleu->GetOne();
    return ScoreP(res);
  }
  ScoreP GetZero() const {
    BLEUCBLEUCombinationScore* res = new BLEUCBLEUCombinationScore;
    res->bleu = bleu->GetZero();
    res->cbleu = cbleu->GetZero();
    return ScoreP(res);
  }
  void Subtract(const Score& rhs, Score* res) const {
    bleu->Subtract(*static_cast<const BLEUCBLEUCombinationScore&>(rhs).bleu,
                   static_cast<BLEUCBLEUCombinationScore*>(res)->bleu.get());
    cbleu->Subtract(*static_cast<const BLEUCBLEUCombinationScore&>(rhs).cbleu,
                  static_cast<BLEUCBLEUCombinationScore*>(res)->cbleu.get());
  }
  void Encode(std::string* out) const {
    string bs, ts;
    bleu->Encode(&bs);
    cbleu->Encode(&ts);
    out->clear();
    (*out) += static_cast<char>(bs.size());
    (*out) += bs;
    (*out) += ts;
  }
  bool IsAdditiveIdentity() const {
    return bleu->IsAdditiveIdentity() && cbleu->IsAdditiveIdentity();
  }
 private:
  ScoreP bleu;
  ScoreP cbleu;
};

BLEUCBLEUCombinationScore::~BLEUCBLEUCombinationScore() {
}

BLEUCBLEUCombinationScorer::BLEUCBLEUCombinationScorer(const vector<vector<WordID> >& refs) {
  bleu_ = SentenceScorer::CreateSentenceScorer(IBM_BLEU, refs);
  cbleu_ = SentenceScorer::CreateSentenceScorer(CBLEU, refs);
}

BLEUCBLEUCombinationScorer::~BLEUCBLEUCombinationScorer() {
}

ScoreP BLEUCBLEUCombinationScorer::ScoreCCandidate(const vector<WordID>& hyp) const {
  return ScoreP();
}

ScoreP BLEUCBLEUCombinationScorer::ScoreCandidate(const std::vector<WordID>& hyp) const {
  BLEUCBLEUCombinationScore* res = new BLEUCBLEUCombinationScore;
  res->bleu = bleu_->ScoreCandidate(hyp);
  res->cbleu = cbleu_->ScoreCandidate(hyp);
  return ScoreP(res);
}

ScoreP BLEUCBLEUCombinationScorer::ScoreFromString(const std::string& in) {
  int bss = in[0];
  BLEUCBLEUCombinationScore* r = new BLEUCBLEUCombinationScore;
  r->bleu = SentenceScorer::CreateScoreFromString(IBM_BLEU, in.substr(1, bss));
  r->cbleu = SentenceScorer::CreateScoreFromString(CBLEU, in.substr(1 + bss));
  return ScoreP(r);
}
