from argparse import ArgumentParser
import time

class RunMCE:
    def __init__(self):
        self.run_code2vec = False
        self.run_codebert = False
        self.run_sbert = False
        self.train_code2vec = False
        self.train_codebert = False
        self.run_codebert_base = False
    
    @classmethod   
    def args_parser(cls) -> ArgumentParser:
        parser = ArgumentParser(description="Run MultiCodeEmbed")
        parser.add_argument('-Tc', "--train_code2vec", action="store_true", help="Train Code2Vec")
        parser.add_argument('-Rc', "--run_code2vec", action="store_true", help="Run Code2Vec")
        parser.add_argument('-RC', "--run_codebert", action="store_true", help="Run CodeBERT")
        g1 = parser.add_mutually_exclusive_group()
        g1.add_argument('-B', "--run_codebert_base", action="store_true", help="Run CodeBERT Use Base (Not use fine-tuned weights)")
        g1.add_argument('-TC', "--train_codebert", action="store_true", help="Train CodeBERT")
        parser.add_argument('-RS', "--run_sbert", action="store_true", help="Run SBERT")
        return parser
    
    def load_from_args(self):
        args = self.args_parser().parse_args()
        self.run_code2vec = args.run_code2vec
        self.run_codebert = args.run_codebert
        self.run_sbert = args.run_sbert
        self.train_code2vec = args.train_code2vec
        self.train_codebert = args.train_codebert
        self.run_codebert_base = args.run_codebert_base

    @staticmethod
    def time_output(time_diff):
        if time_diff < 60:
            return f"{time_diff:.2f} seconds"
        elif time_diff < 3600:
            return f"{time_diff // 60} minutes {time_diff % 60:.2f} seconds"
        else:
            return f"{time_diff // 3600} hours {time_diff % 3600 // 60} minutes {time_diff % 60:.2f} seconds"

    def run(self):
        print("[MultiCodeEmbed] Start...")
        start_time = time.time()
        
        if self.train_code2vec:
            print("[MultiCodeEmbed] Training code2Vec...")
            import BuildASTMinerForcode2vec
            BuildASTMinerForcode2vec.main()
            import code2vec_1train
            code2vec_1train.main()
            import code2vec_2release
            code2vec_2release.main()
            print("[MultiCodeEmbed] code2vec train completed.")
            
        if self.run_code2vec:
            print("[MultiCodeEmbed] Running code2Vec...")
            if not self.train_code2vec:
                import BuildASTMinerForcode2vec
                BuildASTMinerForcode2vec.build_astminer()
            import code2vec_3embedding
            code2vec_3embedding.main()
            print("[MultiCodeEmbed] code2vec run completed.")            

        if self.train_codebert:
            print("[MultiCodeEmbed] Training CodeBERT...")
            import getAllData
            all_datasets = getAllData.get_all_data_files()
            import CodeBERT_1train
            for dataset in all_datasets:
                if dataset.endswith('.jsonl') and '_train' not in dataset and '_valid' not in dataset and '_test' not in dataset:
                    CodeBERT_1train.train(dataset)
            print("[MultiCodeEmbed] CodeBERT train completed.")
            
        if self.run_codebert:
            print("[MultiCodeEmbed] Running CodeBERT...")
            import CodeBERT_2embedding
            if self.run_codebert_base:
                CodeBERT_2embedding.main(False)
            else:
                CodeBERT_2embedding.main(True)
            print("[MultiCodeEmbed] CodeBERT run completed.")

        if self.run_sbert:
            print("[MultiCodeEmbed] Running SBERT...")
            import SBERT
            SBERT.main()
            print("[MultiCodeEmbed] SBERT run completed.")
        
        print("[MultiCodeEmbed] All tasks completed.")

        end_time = time.time()
        print(f"[MultiCodeEmbed] Finished in {RunMCE.time_output(end_time - start_time)}.")

if __name__ == "__main__":
    mce = RunMCE()
    mce.load_from_args()
    mce.run()