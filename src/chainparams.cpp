// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The Nodebase developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector <CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count) {
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// todo implement checkpoint block
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
                (0, uint256("0x"));
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1534792829, // * UNIX timestamp of last checkpoint block
        0,    // * total number of transactions between genesis and last checkpoint
        //   (the tx=... number in the SetBestChain debug.log lines)
        2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
                (0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1534792829,
        0,
        250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
                (0, uint256("0x")); // lyra2z
//    (0, uint256("0x000001733877023e9a2751258b8119e420e153377ffd21c996af58c8cdceede5")); // quark
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1534792829,
        0,
        100};

libzerocoin::ZerocoinParams *CChainParams::Zerocoin_Params() const {
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x44;
        pchMessageStart[1] = 0x73;
        pchMessageStart[2] = 0x75;
        pchMessageStart[3] = 0x46;
        vAlertPubKey = ParseHex("04f624e17101fc210e609e161e2ef58745af485e26cabd51681c2c25953958dae5b549d636a73ea94840bc7eb720c43f26f1624596e8f1920ee37732ad9d6001eb");
        nDefaultPort = 22001;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Nodebase starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 1314000;   // HALVING EVERY: 1314000 BLOCKS
        nSubsidyBudgetPercentage = 5;      // Must be less than 100
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 60 * 60; // Nodebase: 1 hr
        nTargetSpacing = 120;  // Nodebase: 2 min
        nMaturity = 10;
        nMasternodeCollateral = 1000; // 1000 NDB
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 600000000LL * COIN;
        nSwiftTxMinFee = 0.01 * COIN;             // 1 CENT or 10000 satoshis
        nMinTxFeePerK = 0.0001 * COIN;            // .01 CENT or 100 satoshis
        nMinRelayTxFeePerK = 0.0001 * COIN;       // .01 CENT or 100 satoshis

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = 0;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = -1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = -1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 0; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 1; //Start enforcing the invalid UTXO's

        const char *pszTimestamp = "NodeBAse chain made with love in Europe,America,Asia Aug 20 2018";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)
                                           << vector<unsigned char>((const unsigned char *) pszTimestamp,
                                                                    (const unsigned char *) pszTimestamp +
                                                                    strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex(
                "04f624e17101fc210e609e161e2ef58745af485e26cabd51681c2c25953958dae5b549d636a73ea94840bc7eb720c43f26f1624596e8f1920ee37732ad9d6001eb")
                                               << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1534792829;

        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1250780;

        hashGenesisBlock = genesis.GetHash();
        assert(genesis.hashMerkleRoot == uint256("0xb2c056261007b6dcd5ecae1b950f5c01a9ed876372f1f73a4c39d143b91542bd"));
        assert(hashGenesisBlock == uint256("0x000007e95600dfaabb7defd2b97ca02f0cb927e41e39f1a239a96f2671895d4c"));

        // Zerocoin, activated never
        nZerocoinStartHeight = INT_MAX;
        nZerocoinStartTime = INT_MAX;

//        vSeeds.push_back(CDNSSeedData("0", "95.179.144.16"));             // Primary DNS Seeder
//        vSeeds.push_back(CDNSSeedData("1", "140.82.54.171"));      // Secondary DNS Seeder
//        vSeeds.push_back(CDNSSeedData("2", "80.240.21.186"));     // Third DNS Seeder

        vFixedSeeds.clear();
        vSeeds.clear();


        // https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);     // starts with B
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 63);     // starts with S
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 75);        // starts with X

        /* if tempted to change below consider https://github.com/bitcoin/bips/blob/master/bip-0043.mediawiki
            Because this scheme can be used to generate nodes for more cryptocurrencies at once,
            or even something totally unrelated to cryptocurrencies, there's no point in using a
            special version magic described in section "Serialization format" of BIP32. We suggest
            to use always 0x0488B21E for public and 0x0488ADE4 for private nodes (leading to
            prefixes "xpub" and "xprv" respectively).
        */

        base58Prefixes[EXT_PUBLIC_KEY] =
                boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container < std::vector < unsigned char > >
                ();
        base58Prefixes[EXT_SECRET_KEY] =
                boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container < std::vector < unsigned char > >
                ();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] =
                boost::assign::list_of(0x80)(0x00)(0x0b)(0x2a).convert_to_container < std::vector < unsigned char > >
                ();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04f624e17101fc210e609e161e2ef58745af485e26cabd51681c2c25953958dae5b549d636a73ea94840bc7eb720c43f26f1624596e8f1920ee37732ad9d6001eb";
        strObfuscationPoolDummyAddress = "D87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = genesis.nTime + 60 * 60; // 1 hr after genesis

        /** Zerocoin */
        // See https://github.com/Zerocoin/libzerocoin/wiki/Generating-Zerocoin-parameters
        // See https://pivx.org/zpiv/
        // http://zerocoin.org/media/pdf/ZerocoinOakland.pdf
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                          "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                          "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                          "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                          "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                          "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData &Checkpoints() const {
        return data;
    }
};

static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0x16;
        pchMessageStart[2] = 0x73;
        pchMessageStart[3] = 0xd7;
        vAlertPubKey = ParseHex(
                "04f624e17101fc210e609e161e2ef58745af485e26cabd51681c2c25953958dae5b549d636a73ea94840bc7eb720c43f26f1624596e8f1920ee37732ad9d6001eb");
        nDefaultPort = 22003;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Nodebase: 1 hr
        nTargetSpacing = 1 * 60;  // Nodebase: 2 min
        nLastPOWBlock = 30;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 600000000LL * COIN;

        // nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        // nBlockRecalculateAccumulators = -1; //Trigger a recalculation of accumulators
        // nBlockFirstFraudulent = -1; //First block that bad serials emerged
        // nBlockLastGoodCheckpoint = 0; //Last valid accumulator checkpoint
        // nBlockEnforceInvalidUTXO = 1; //Start enforcing the invalid UTXO's


        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1530742317;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 728215;

        hashGenesisBlock = genesis.GetHash();
        assert(genesis.hashMerkleRoot == uint256("0xb2c056261007b6dcd5ecae1b950f5c01a9ed876372f1f73a4c39d143b91542bd"));

        assert(hashGenesisBlock == uint256("0x00000e71f6a536e266df67f4a772f9d3ab85915f23b343e1f0bc1c14012f6835"));

        // Zerocoin, activated by default
        nZerocoinStartHeight = INT_MAX;
        nZerocoinStartTime = INT_MAX;

        vFixedSeeds.clear();
        vSeeds.clear();
//        vSeeds.push_back(CDNSSeedData("nodebase.tech", "testnet-seeds.nodebase.tech"));             // Primary DNS Seeder
//        vSeeds.push_back(CDNSSeedData("gig8.com", "testnet-seeds.nodebase.gig8.com"));      // Secondary DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 88); // Testnet nodebase addresses start with 'b''
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,
                                                                    125);  // Testnet nodebase script addresses start with 's'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 137);     // Testnet private keys start with 'x'
        base58Prefixes[EXT_PUBLIC_KEY] =
                boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container < std::vector < unsigned char > >
                ();
        base58Prefixes[EXT_SECRET_KEY] =
                boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container < std::vector < unsigned char > >
                ();
        // Testnet nodebase BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] =
                boost::assign::list_of(0x80)(0x00)(0x00)(0x02).convert_to_container < std::vector < unsigned char > >
                ();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04f624e17101fc210e609e161e2ef58745af485e26cabd51681c2c25953958dae5b549d636a73ea94840bc7eb720c43f26f1624596e8f1920ee37732ad9d6001eb";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = genesis.nTime + 60 * 60; // 1 hr after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
        // here because we only have a 8 block finalization window on testnet
    }

    const Checkpoints::CCheckpointData &Checkpoints() const {
        return dataTestnet;
    }
};

static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0x1d;
        pchMessageStart[2] = 0x71;
        pchMessageStart[3] = 0xd9;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 60 * 60; // Nodebase: 1 hour
        nTargetSpacing = 120;        // Nodebase: 2 min
        bnProofOfWorkLimit = ~uint256(0) >> 1;

        
        genesis.nTime = 1530742317;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 233847;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 22005;
        //assert(hashGenesisBlock == uint256("0x000006ba3bf77872f9c4747ed7451309cfc89c85f6b74f19254868211162de4a"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData &Checkpoints() const {
        return dataRegtest;
    }
};

static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 37006;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData &Checkpoints() const {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void
    setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }

    virtual void setEnforceBlockUpgradeMajority(
            int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }

    virtual void setRejectBlockOutdatedMajority(
            int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }

    virtual void setToCheckBlockUpgradeMajority(
            int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }

    virtual void setDefaultConsistencyChecks(
            bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }

    virtual void setAllowMinDifficultyBlocks(
            bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }

    virtual void
    setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams() {
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams *) &unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine() {
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
