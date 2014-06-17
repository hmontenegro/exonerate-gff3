/****************************************************************\
*                                                                *
*  Analysis module for exonerate                                 *
*                                                                *
*  Guy St.C. Slater..   mailto:guy@ebi.ac.uk                     *
*  Copyright (C) 2000-2008.  All Rights Reserved.                *
*                                                                *
*  This source code is distributed under the terms of the        *
*  GNU General Public License, version 3. See the file COPYING   *
*  or http://www.gnu.org/licenses/gpl.txt for details            *
*                                                                *
*  If you use this code, please keep this notice intact.         *
*                                                                *
\****************************************************************/

#ifndef INCLUDED_ANALYSIS_H
#define INCLUDED_ANALYSIS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <glib.h>

#include "fastapipe.h"
#include "gam.h"
#include "bsam.h"
#include "argument.h"
#include "submat.h"
#include "seeder.h"
#include "comparison.h"
#include "socket.h"

typedef struct {
    gboolean  use_exhaustive;
    gboolean  use_bigseq;
       gchar *force_scan;
        gint  saturate_threshold;
       gchar *custom_server_command;
} Analysis_ArgumentSet;

Analysis_ArgumentSet *Analysis_ArgumentSet_create(Argument *arg);

/**/

typedef struct {
           SocketClient  *sc;
                   gint   verbosity;
               Alphabet  *server_alphabet;
               gboolean   is_masked;
                guint64   num_seqs;
                guint64   max_seq_len;
                guint64   total_seq_len;
                /**/
                FastaDB  *probe_fdb;
               Sequence  *curr_query;
               Sequence **seq_cache;
} Analysis_Client;

typedef struct {
               FastaPipe *fasta_pipe;
                     GAM *gam;
                    BSAM *bsam;
    Analysis_ArgumentSet *aas;
             FastaDB_Seq *curr_query;
                  Seeder *curr_seeder;
                gboolean  scan_query;
        Comparison_Param *comparison_param;
                    gint  verbosity;
         Analysis_Client *query_ac;
         Analysis_Client *target_ac;
} Analysis;

Analysis *Analysis_create(
              GPtrArray *query_path_list, Alphabet_Type query_type,
              gint query_chunk_id, gint query_chunk_total,
              GPtrArray *target_path_list, Alphabet_Type target_type,
              gint target_chunk_id, gint target_chunk_total,
              gint verbosity);
void  Analysis_destroy(Analysis *analysis);

void Analysis_process(Analysis *analysis);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUDED_ANALYSIS_H */

